#ifndef BALL_H
#define BALL_H

#include "types.h"
#include "defines.h"
#include <SDL.h>

class Ball {
public:
    Pos pos;
    Vel vel;

    bool isIn;
    //int number;
    //SDL_Texture* sprite;

    void update();
    float velocityNorm();
    float movementAngle();
    bool isMoving();

    //void draw();
};

#endif