#ifndef BALL_H
#define BALL_H

#include "types.h"
#include "defines.h"

class Ball {
public:
    Pos pos;
    Vel vel;
    bool isIn;

    void update();
    float velocityNorm();
    float movementAngle();
    bool isMoving();
};

#endif