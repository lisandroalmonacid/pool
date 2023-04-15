#ifndef GAME_H
#define GAME_H

#include "physics.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Ball.h"

class Game {
public:
  Game();
  void mainMenuScreen();
  void game_screen();
  void gameLoop();
  void start();
  void finish(int winner);
  void quitGame();

  void updateBalls();
  void manageBallCollisions();
  void manageBorderCollisions(Ball* b);
  void processEventQueue();
  void render();

private:
  bool KEYS[322];  // 322 is the number of SDLK_DOWN events
  int mouseX;
  int mouseY;
  bool mouseClick;
  int shotForce;
  Action action;
  std::vector<Ball*> balls;
};

#endif