#include <SDL.h>
//#include "render.h"
#include "Game.h"
#include <iostream>

int main(int argc, char** args) {
    std::cout << "Launching game." << std::endl;
    Game* game = new Game();
    game->start();
    delete(game);

}
