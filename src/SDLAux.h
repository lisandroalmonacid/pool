#ifndef SDLAUX_H
#define SDLAUX_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
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
void drawBallTrajectory(std::vector<Ball*> balls, float mouseX, float cueAngle);
void drawWallCollision(Ball* b, Pos l1, Pos l2);
void drawBallCollision(Ball* b1, Ball* b2);

SDL_Texture* createTextTexture(TTF_Font* font, char* text, SDL_Color color);

#endif