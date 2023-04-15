#include "Game.h"
#include <iostream>
#include "SDLAux.h"

Game::Game() {
    //Init KEYS
    for(int i = 0; i < 322; i++) {
        KEYS[i] = false;
    }
    mouseClick = false;
    shotForce = 0;

    for (int i = 0; i < 16; i++) {
	    Ball* b = new Ball(startingPositions[i], i);
        balls.push_back(b);
    }
}

void Game::start() {
    std::cout << "Starting game" << std::endl;
    
    while (action != quit) {
        switch (action) {
        case mainMenu:
            mainMenuScreen();
            break;
        case game:
            gameLoop();
            break;
        default:
            break;
        }
    }
    quitGame();
    return;
}

void Game::mainMenuScreen() {
    std::cout << "Main menu!" << std::endl;
    SDL_RenderCopy(rend, mainMenuTexture, nullptr, nullptr); //draw main menu
    SDL_RenderPresent(rend);
    while(action == mainMenu) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                KEYS[event.key.keysym.sym] = true;
            }
        }
        if (KEYS[SDLK_SPACE]) {
            KEYS[SDLK_SPACE] = false;
            action = game;
        }
        if (KEYS[SDLK_ESCAPE]) {
            KEYS[SDLK_ESCAPE] = false;
            action = quit;
        }
    }
    std::cout << "Leaving main menu." << std::endl;
    return;
}

void Game::gameLoop() {
    while(action == game) {
        processEventQueue();

        if (ballsMoving(balls)) {
            updateBalls();
            manageBallCollisions();
        } else {
            if (balls[0]->isIn) {
                balls[0]->isIn = false;
                balls[0]->pos = startingPositions[0];
                balls[0]->vel = {0, 0};
            }

            if (mouseClick) {
                if (shotForce < 25) shotForce = shotForce + 2;
            } else {
                float cueAngle = angleBetweenPoints(balls[0]->pos, {mouseX, mouseY});
                balls[0]->vel.x = shotForce * cos(cueAngle);
                balls[0]->vel.y = shotForce * sin(cueAngle);
                shotForce = 0;
            }
        }
        render();
    }
}

void Game::updateBalls() {
    for (int i = 0; i < balls.size(); i++) {
        if (balls[i]->isMoving()) {
            balls[i]->update();
            manageBorderCollisions(balls[i]);
        }
    }
}

void Game::manageBallCollisions() {
    for (int i = 0; i < balls.size(); i++) {
        for (int j = i + 1; j < balls.size(); j++){
            if (ballsAreColliding(balls[i], balls[j]))
                ballCollision(balls[i], balls[j]);
        }
    }
}

void Game::manageBorderCollisions(Ball* b) {
    for (int i = 1; i < 25; i++) {
        if (isBallCollidingWithWall(b, tableEdges[i-1], tableEdges[i])) {
            if (i % 4 == 0) {
                b->isIn = true;
                b->pos = inPositions[b->number];
                b->vel = {0, 0};
            } else {
                borderCollision(b, tableEdges[i-1], tableEdges[i]);
            }
        }
    }
}

void Game::processEventQueue() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            KEYS[event.key.keysym.sym] = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            mouseClick = true;
            break;
        case SDL_MOUSEBUTTONUP:
            mouseClick = false;
            break;
        case SDL_QUIT:
            action = quit;
            break;
        default:
            break;
        }
    }

    SDL_GetMouseState(&mouseX, &mouseY);

    if (KEYS[SDLK_ESCAPE]) {
        KEYS[SDLK_ESCAPE] = false;
        action = quit;
    }
    if (KEYS[SDLK_r]) {
        KEYS[SDLK_r] = false;
        action = mainMenu;
    }
}

void Game::render() {
    SDL_RenderCopy(rend, tableTexture, nullptr, nullptr); //draw table
    
    for (int i = 0; i < balls.size(); i++)
        balls[i]->draw();

    if (!ballsMoving(balls)) {
        //draw cue
        float cueAngle = angleBetweenPoints(balls[0]->pos, {mouseX, mouseY});
        float x = ((cueW + 2*ballRadius + shotForce*4) * cos(cueAngle) + cueW)/2;
        float y = ((cueW + 2*ballRadius + shotForce*4) * sin(cueAngle) + cueH)/2;
        SDL_Rect dstRect = {balls[0]->pos.x - x, balls[0]->pos.y - y, cueW, cueH};
        SDL_RenderCopyEx(rend, cueTexture, nullptr, &dstRect, (cueAngle) * 180 / M_PI, nullptr, SDL_FLIP_HORIZONTAL);

        //drawBallTrajectory(balls, mouseX, cueAngle);
    }

    SDL_RenderPresent(rend);
    SDL_Delay(17);
    SDL_RenderClear(rend);
}

void Game::finish(int winner) {
	quitGame();
}

void Game::quitGame() {
    std::cout << "quitting!" << std::endl;
    for (int i = 0; i < balls.size(); i++) {
        delete(balls[i]);
    }
    SDL_DestroyTexture(tableTexture);
    SDL_DestroyTexture(mainMenuTexture);
    SDL_DestroyTexture(cueTexture);
    SDL_DestroyTexture(triangleTexture);
}
