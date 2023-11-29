#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Game.h"
#include "SDLAux.h"
#include "Texture.h"
#include <iostream>

GameState gameState;

SDL_Event event;
SDL_Window* win;
SDL_Renderer* rend;

Texture* tableTexture;
Texture* mainMenuTexture;
Texture* cueTexture;
Texture* triangleTexture;
Texture* trajectoryBallTexture;
Texture* ballTextures[16];
Texture* messageTextures[msgAmount];
Texture* titleTexture;
Texture* subtitleTexture;

bool init() {
    //Init SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        std::cout <<  "SDL could not initialize! SDL_Error:" << SDL_GetError() << std::endl;
        return false;
    }

    //Init IMG
    if( IMG_Init( IMG_INIT_PNG ) < 0 ) {
        std::cout <<  "SDL image could not initialize! SDL_Error:" << IMG_GetError() << std::endl;
        return false;
    }

    //Init TTF
    if ( TTF_Init() < 0 ) {
        std::cout <<  "SDL ttf could not initialize! SDL_Error:" << TTF_GetError() << std::endl;
        return false;
    }

    //Init Window and Renderer
    win = SDL_CreateWindow("Pool", 10, 10, screenW, screenH, 0);
    rend = SDL_CreateRenderer(win, -1, 0);
    SDL_RenderClear(rend);

    return true;
}

bool loadMedia() {
    tableTexture = new Texture(rend);
    mainMenuTexture = new Texture(rend);
    cueTexture = new Texture(rend);
    triangleTexture = new Texture(rend);

    tableTexture->loadFromFile("img/table.png");
    tableTexture->_w = tableScreenW; tableTexture->_h = tableScreenH;
    mainMenuTexture->loadFromFile("img/mainMenu.png");
    cueTexture->loadFromFile("img/cue.png");
    cueTexture->_usesRotation = true;
    triangleTexture->loadFromFile("img/triangle.png");

    for (int i = 0; i < 16; i++) {
        ballTextures[i] = new Texture(rend);
        ballTextures[i]->loadFromFile(("img/ball_" + std::to_string(i) + ".png").c_str());
    }

    TTF_Font* titleFont = TTF_OpenFont("fonts/BRITANIC.ttf", 100);
    TTF_Font* subtitleFont = TTF_OpenFont("fonts/BRITANIC.ttf", 50);
    TTF_Font* textBigFont = TTF_OpenFont("fonts/BRITANIC.ttf", 50);
    TTF_Font* textSmallFont = TTF_OpenFont("fonts/BRITANIC.ttf", 50);

    titleTexture = new Texture(rend);
    titleTexture->loadFromText("POOL", titleFont, colorWhite);
    subtitleTexture = new Texture(rend);
    subtitleTexture->loadFromText("PRESS SPACE TO PLAY", subtitleFont, colorWhite);

    for (int i = 0; i < msgAmount; i++) {
        messageTextures[i] = new Texture(rend);
        messageTextures[i]->loadFromText(messages[i].c_str(), textBigFont, colorWhite);
    }

    return true;
}

bool quit() {
    tableTexture->freeTexture();
    mainMenuTexture->freeTexture();
    cueTexture->freeTexture();
    triangleTexture->freeTexture();
    
    for (int i = 0; i < 16; i++)
        ballTextures[i]->freeTexture();

    for (int i = 0; i < msgAmount; i++)
        messageTextures[i]->freeTexture();


    TTF_Quit();
    IMG_Quit();

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return true;
}

int main(int argc, char** args) {

    std::cout << "Launching..." << std::endl; 

    if (!init()) {
        std::cout << "Error on initialization." << std::endl;
        return -1;
    }

    std::cout << "Game initialized." << std::endl; 

    if (!loadMedia()) {
        std::cout << "Error on loading media." << std::endl;
        return -1;
    }

    std::cout << "Media loaded. About to start the Pool." << std::endl;

    Game* game = new Game();
    game->start();
    delete(game);

    quit();

    return 0;
}
