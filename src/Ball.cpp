#include "Ball.h"
#include <iostream>

Ball::Ball(Pos startPos, int nbr) : pos(startPos), vel({0, 0}), isIn(false), number(nbr) {
    std::string filepath = "img/ball_" + std::to_string(number) + ".png";
    texture = IMG_LoadTexture(rend, filepath.c_str());
    dstRect = { (int)(pos.x - ballRadius), (int)(pos.y - ballRadius), (int)(2*ballRadius),  (int)(2*ballRadius)};
}

Ball::~Ball() {
    SDL_DestroyTexture(texture);
}

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

void Ball::draw() {
    dstRect = { (int)(pos.x - ballRadius), (int)(pos.y - ballRadius), (int)(2*ballRadius),  (int)(2*ballRadius)};
    SDL_RenderCopy(rend, this->texture, nullptr, &dstRect);
}