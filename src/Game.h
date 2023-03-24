#ifndef GAME_H
#define GAME_H

#include "physics.h"
#include <SDL.h>
#include "SDLAux.h"

class Game {
public:
  Game();
  void main_menu_screen();
  void game_screen();
  void game_loop();
  void start();
  void finish(int winner);
  void quitGame();

  void update(); //better name?

private:
  SDL_Event event;
  SDL_Window* win;
  SDL_Surface* screenSurface;
  SDL_Renderer* rend;
  bool KEYS[322];  // 322 is the number of SDLK_DOWN events
  Action action;
  Ball balls[16];
  SDL_Rect src_rects[16];
  SDL_Rect dst_rects[16];
};

#endif