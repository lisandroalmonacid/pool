#ifndef BALL_H
#define BALL_H

#include "types.h"
#include "defines.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Ball {
public:
    Ball(Pos startPos, int nbr);
    ~Ball();

    Pos pos;
    Vel vel;

    bool isIn;
    int number;
    SDL_Texture* texture;
    SDL_Rect dstRect;

    void update();
    float velocityNorm();
    float movementAngle();
    bool isMoving();

    void draw();
};

#endif