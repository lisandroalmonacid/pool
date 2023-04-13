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
    std::cout << "init balls" << std::endl;
    for (int i = 0; i < 16; i++) {
	    Ball* b = new Ball(startingPositions[i], i);
        balls.push_back(b);
    }
    std::cout << "done" << std::endl;
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
    std::cout << "game loop!" << std::endl;
    while(action == game) {
        SDL_RenderCopy(rend, tableTexture, nullptr, nullptr); //draw table

        for (int i = 0; i < balls.size(); i++)
            balls[i]->draw();

        if (ballsMoving(balls)) {
            updateBalls();
            for (int i = 0; i < balls.size(); i++) {
                if (balls[i]->isIn) {
                    balls.erase(balls.begin() + i);
                }
            }
            manageCollisions();
        } else {
            //draw cue
            SDL_GetMouseState(&mouseX, &mouseY);
            float cueAngle = angleBetweenPoints(balls[0]->pos, {mouseX, mouseY});
            float x = ((cueW + 2*ballRadius + shotForce) * cos(cueAngle) + cueW)/2;
            float y = ((cueW + 2*ballRadius + shotForce) * sin(cueAngle) + cueH)/2;
            SDL_Rect dstRect = {balls[0]->pos.x - x, balls[0]->pos.y - y, cueW, cueH};
            SDL_RenderCopyEx(rend, cueTexture, nullptr, &dstRect, (cueAngle) * 180 / M_PI, nullptr, SDL_FLIP_HORIZONTAL);

            //drawBallTrajectory(balls, mouseX, cueAngle);
            
        }
        SDL_RenderPresent(rend);
        SDL_Delay(17);
        SDL_RenderClear(rend);

        //Get input
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

        //shot!
        if (!(ballsMoving(balls))) {
            if (mouseClick) {
                if (shotForce < 100) shotForce = shotForce + 2;
            } else {
                SDL_GetMouseState(&mouseX, &mouseY);
                float cueAngle = angleBetweenPoints({mouseX, mouseY}, balls[0]->pos);
                balls[0]->vel.x = shotForce/4 * cos(cueAngle + M_PI);
                balls[0]->vel.y = shotForce/4 * sin(cueAngle + M_PI);
                shotForce = 0;
            }
        }

        //si es escape, hago break
        if (KEYS[SDLK_ESCAPE]) {
            KEYS[SDLK_ESCAPE] = false;
            action = quit;
        }
        if (KEYS[SDLK_r]) {
            KEYS[SDLK_r] = false;
            action = mainMenu;
        }
    }
    switch (action) {
    case mainMenu:
        mainMenuScreen();
        break;
    case quit:
        quitGame();
    default:
        break;
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

void Game::manageCollisions() {
    for (int i = 0; i < balls.size(); i++) {
        for (int j = i + 1; j < balls.size(); j++){
            if (ballsAreColliding(balls[i], balls[j]))
                manageCollision(balls[i], balls[j]);
        }
    }
}

void Game::manageBorderCollisions(Ball* b) {
    for (int i = 1; i < 25; i++) {
        if (isBallCollidingWithWall(b, tableEdges[i-1], tableEdges[i])) {
            if (i % 4 == 0) {
                b->isIn = true;
            } else {
                manageBorderCollision(b, tableEdges[i-1], tableEdges[i]);
            }
        }
    }
}

void Game::finish(int winner) {
	quitGame();
}

void Game::quitGame() {
    for (int i = 0; i < balls.size(); i++) {
        delete(balls[i]);
    }
    SDL_DestroyTexture(tableTexture);
    SDL_DestroyTexture(mainMenuTexture);
    SDL_DestroyTexture(cueTexture);
    SDL_DestroyTexture(triangleTexture);
}
