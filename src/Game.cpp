#include "Game.h"
#include <iostream>

Game::Game() {

    //Init KEYS
    for(int i = 0; i < 322; i++) { // init them all to false
        KEYS[i] = false;
    }

    for (int i = 0; i < 16; i++)    
	    balls[i] = {startingPositions[i], {0, 0}, false};

    //Init Source Rectangles
    for (int i = 0; i < 8; i++) {
        src_rects[i].x = i * 230;
        src_rects[i].y = 0;
        src_rects[i].w = 215;
        src_rects[i].h = 215;
    }

    for (int i = 8; i < 16; i++) {
        src_rects[i].x = (i - 8) * 230;
        src_rects[i].y = 240;
        src_rects[i].w = 215;
        src_rects[i].h = 215;
    }

    //Init Destination Rectangles
    for (int i = 0; i < 16; i++) {
        dst_rects[i].x = balls[i].pos.x - ballRadius;
        dst_rects[i].y = balls[i].pos.y - ballRadius;
        dst_rects[i].w = ballRadius * 2;
        dst_rects[i].h = ballRadius * 2;
    }
    
}

void Game::start() {
    main_menu_screen();
    if (action == quit) {
        quitGame();
    } else if (action == game) {
        game_loop();
    }
    return;
}

void Game::main_menu_screen() {
    drawMainMenuScreen();

    while(1) {
        //poll Enter Key
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                std::cout << "You pressed this key: " << event.key.keysym.sym << std::endl;
                KEYS[event.key.keysym.sym] = true;
                break;
            }
        }

        if (KEYS[SDLK_SPACE]) {
            //enter = 13
            action = game;
            break;
        }
        if (KEYS[SDLK_ESCAPE]) {
            action = quit;
            break;
        }
    }
    std::cout << "Leaving main menu." << std::endl;
    return;
}

void Game::game_loop() {
    while(1) {
        drawTable();
        drawBalls(balls);
        if (ballsMoving(balls)) {
            updateBalls();
            manageCollisions();
        } else {
            drawCue(balls);
        }
        SDL_UpdateWindowSurface(win);
        SDL_Delay(17);
        //Get input
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                KEYS[event.key.keysym.sym] = true;
                break;
            }
        }
        //si es space, aplico velocidad
        if (KEYS[SDLK_SPACE]) {
            balls[0].vel.x = 10; balls[0].vel.y = 10;
            KEYS[SDLK_SPACE] = false;
        //si es escape, hago break
        } else if (KEYS[SDLK_ESCAPE]) {
            action = quit;
            break;
        }
    }
    if (action == quit) {
        quitGame();
    }
}

void Game::updateBalls() {
    for (int i = 0; i < 16; i++) {
        if (balls[i].isMoving()) {
            balls[i].update();
            manageBorderCollisions(&balls[i]);
        }
    }
}

void Game::manageCollisions() {
    for (int i = 0; i < 16; i++) {
        for (int j = i + 1; j < 16; j++){
            if (ballsAreColliding(&balls[i], &balls[j]))
                manageCollision(&balls[i], &balls[j]);
        }
    }
}

void Game::finish(int winner) {
	quitGame();
}

void Game::quitGame() {
    SDL_FreeSurface(screenSurface);
    SDL_FreeSurface(tableSurface);
    SDL_FreeSurface(mainMenuSurface);
    SDL_FreeSurface(ballsSurface);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
