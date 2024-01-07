#ifndef BALL_H
#define BALL_H

#include "../types.h"
#include "../globals.h"
#include "GameObject.h"
#include <string>

class Ball : public GameObject {
public:
    Ball(Pos startPos, int nbr);
    ~Ball();
    void draw() override;

    Pos pos;
    Vel vel;

    bool isIn;
    int number;
    bool isCollidingWithWall;
    BallClass _class;
    Texture* _texture;

    void update();
    double movementAngle();
    bool isMoving();

    Pos drawPos();
    Pos screenPos();
};

#endif