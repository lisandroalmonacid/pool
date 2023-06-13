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
    bool isCollidingWithWall;
    BallClass _class;
    Texture* _texture;

    void update();
    float movementAngle();
    bool isMoving();

    void draw();
    SDL_Point drawPos();
    SDL_Point screenPos();
};

#endif