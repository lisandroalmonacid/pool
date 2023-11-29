#include "Game.h"
#include <iostream>
#include "SDLAux.h"
#include <cmath>

Game::Game() {
    //Init KEYS
    for(int i = 0; i < 322; i++) {
        gameState.KEYS[i] = false;
    }
    gameState.mouseClick = false;
    gameState.action = MainMenu;

    mainMenuScene = new MainMenuScene();
    poolScene = new PoolScene();
    currentScene = mainMenuScene;
}

void Game::start() {
    currentScene = mainMenuScene;
    currentScene->init();

    int t = 0;

    while (gameState.action != Quit) {
        processEventQueue();

        t++;
        if (t == 100) {
            render();
            t = 0;
        }

        gameState.action = currentScene->loop();

        Scene* nextScene;
        switch (gameState.action) {
        case MainMenu:
            nextScene = mainMenuScene;
            break;
        case Pool:
            nextScene = poolScene;
            break;
        default:
            break;
        }
        if (currentScene != nextScene)
            switchScenes(nextScene);
    }
    quitGame();
}
void Game::processEventQueue() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            gameState.KEYS[event.key.keysym.sym] = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            gameState.mouseClick = true;
            break;
        case SDL_MOUSEBUTTONUP:
            gameState.mouseClick = false;
            break;
        case SDL_QUIT:
            gameState.action = Quit;
            break;
        default:
            break;
        }
    }

    SDL_GetMouseState(&gameState.mouseX, &gameState.mouseY);

    if (gameState.KEYS[SDLK_ESCAPE]) {
        gameState.KEYS[SDLK_ESCAPE] = false;
        gameState.action = Quit;
    }
    if (gameState.KEYS[SDLK_r]) {
        gameState.KEYS[SDLK_r] = false;
        gameState.action = MainMenu;
    }
}

void Game::render() {
    currentScene->render();
    SDL_RenderPresent(rend);
    SDL_Delay(17);
    SDL_RenderClear(rend);
}

void Game::switchScenes(Scene *newScene) {
    currentScene->exit();
    currentScene = newScene;
    currentScene->init();
}

void Game::quitGame() {}