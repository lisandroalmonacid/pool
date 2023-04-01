#ifndef SDLAUX_H
#define SDLAUX_H

#include <SDL.h>
#include "types.h"
#include "defines.h"
#include "Ball.h"

void drawCircle(Pos center, float radius, Color Color);
void drawRect(Pos start, int width, int height, Color color);
void drawMainMenuScreen();
void drawTable();
void drawBalls(Ball* balls);
void drawCue(Ball* balls);
void drawBMP(Pos startPos, char* filepath);

#endif