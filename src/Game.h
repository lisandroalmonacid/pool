#ifndef GAME_H
#define GAME_H

#include "physics.h"
#include <SDL.h>
#include "SDLAux.h"
#include "Ball.h"

class Game {
public:
  Game();
  void main_menu_screen();
  void game_screen();
  void game_loop();
  void start();
  void finish(int winner);
  void quitGame();

  void updateBalls();
  void manageCollisions();

private:
  bool KEYS[322];  // 322 is the number of SDLK_DOWN events
  Action action;
  Ball balls[16];
};

#endif