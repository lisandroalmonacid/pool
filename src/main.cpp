#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include <iostream>

SDL_Event event;
SDL_Window* win;
SDL_Renderer* rend;

SDL_Texture* tableTexture;
SDL_Texture* mainMenuTexture;
SDL_Texture* cueTexture;
SDL_Texture* triangleTexture;
SDL_Texture* trajectoryBallTexture;

int main(int argc, char** args) {
    std::cout << "Launching game." << std::endl;

    //Init SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        std::cout <<  "SDL could not initialize! SDL_Error:" << SDL_GetError() << std::endl;
    }

    SDL_PollEvent(&event);
    std::cout << "before image." << std::endl;
    //Init IMG
    if( IMG_Init( IMG_INIT_PNG ) < 0 ) {
        std::cout <<  "SDL image could not initialize! SDL_Error:" << IMG_GetError() << std::endl;
    }

    std::cout << "after image." << std::endl;

    //Init Window and Renderer
    win = SDL_CreateWindow("Pool", 10, 10, horizontalScreenSize, verticalScreenSize, 0);
    rend = SDL_CreateRenderer(win, -1, 0);
    SDL_RenderClear(rend);

    std::cout << "Window and render initialized." << std::endl;

    //Init Textures
    tableTexture = IMG_LoadTexture(rend, "img/table.png");
    mainMenuTexture = IMG_LoadTexture(rend, "img/mainMenu.png");
    cueTexture = IMG_LoadTexture(rend, "img/cueRotated.png");
    triangleTexture = IMG_LoadTexture(rend, "img/triangle.png");
    trajectoryBallTexture = IMG_LoadTexture(rend, "img/trajectoryBall.png");

    Game* game = new Game();
    game->start();
    delete(game);

    IMG_Quit();

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

}
