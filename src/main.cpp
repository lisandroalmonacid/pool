#include <SDL.h>
#include "Game.h"
#include <iostream>

SDL_Event event;
SDL_Window* win;
SDL_Surface* screenSurface;
SDL_Surface* tableSurface;
SDL_Surface* ballsSurface;
SDL_Surface* mainMenuSurface;
SDL_Rect src_rects[16];
SDL_Rect dst_rects[16];
SDL_Renderer* rend;

int main(int argc, char** args) {
    std::cout << "Launching game." << std::endl;

    //Init SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        std::cout <<  "SDL could not initialize! SDL_Error:" << SDL_GetError() << std::endl;
    }

    //Init Surfaces
    mainMenuSurface = SDL_LoadBMP("../img/mainMenu.bmp");
    ballsSurface = SDL_LoadBMP("../img/balls.bmp");
    tableSurface = SDL_LoadBMP("../img/pool-table.bmp");

    //Init Window and Renderer
    win = SDL_CreateWindow("Pool", 10, 10, horizontalScreenSize, verticalScreenSize, 0);
    
    //Get window surface
    screenSurface = SDL_GetWindowSurface(win);
    rend = SDL_CreateRenderer(win, -1, 0);
    SDL_RenderClear(rend);

    Game* game = new Game();
    game->start();
    delete(game);

}
