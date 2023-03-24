#ifndef SDLAUX_H
#define SDLAUX_H

#include <SDL.h>
#include "types.h"
#include "defines.h"

void drawCircle(SDL_Renderer* rend, Pos center, float radius, Color Color);
void drawRect(SDL_Renderer* rend, Pos start, int width, int height, Color color);
void drawMainMenuScreen(SDL_Renderer* rend);
void drawTable(SDL_Renderer* rend, SDL_Surface* screenSurface);
void drawBalls(SDL_Renderer* rend, Ball* balls);
void drawBMP(SDL_Renderer* rend, Pos startPos, char* filepath);

#endif