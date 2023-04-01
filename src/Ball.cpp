#include "Ball.h"

void Ball::update() {
    pos.x += vel.x;
    pos.y += vel.y;
    if (vel.x > 0)
        vel.x -= abs(frictionEffect * cos(movementAngle()));
    else
        vel.x += abs(frictionEffect * cos(movementAngle()));
    
    if (vel.y > 0)
        vel.y -= abs(frictionEffect * sin(movementAngle()));
    else
        vel.y += abs(frictionEffect * sin(movementAngle()));

    if (abs(vel.x) < minVelocity) vel.x = 0;
    if (abs(vel.y) < minVelocity) vel.y = 0;
}

float Ball::velocityNorm() { return sqrt(pow(vel.x, 2) + pow(vel.y, 2)); }

float Ball::movementAngle() { return fmod(atan(vel.y/vel.x) + 2*M_PI, 2*M_PI); }

bool Ball::isMoving() { return vel.x != 0 || vel.y != 0; }