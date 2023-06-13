#include "Ball.h"
#include <iostream>

Ball::Ball(Pos startPos, int nbr) : pos(startPos), vel({0, 0}), isIn(false), number(nbr), isCollidingWithWall(false) {
    _texture = ballTextures[nbr];
    _texture->_w = 2*ballRadius*tableScreenW/tableW;
    _texture->_h = 2*ballRadius*tableScreenH/tableH;

    if (nbr == 0) {
        _class = cueBall;
    } else if (nbr < 8) {
        _class = Solid;
    } else if (nbr == 8) {
        _class = Black;
    } else {
        _class = Striped;
    }
}

Ball::~Ball() {
    _texture = nullptr;
}

void Ball::update() {
    pos += vel;

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

float Ball::movementAngle() { return fmod(atan(vel.y/vel.x) + 2*M_PI, 2*M_PI); }

bool Ball::isMoving() { return vel.x != 0 || vel.y != 0; }

void Ball::draw() {
    _texture->draw(drawPos());
}

SDL_Point Ball::drawPos() {
    Pos drawPos = pos - ballRadius;
    Pos tableScreenPos = {tableScreenOffsetX, tableScreenOffsetY};
    Vector2d tableDim = {tableW, tableH};
    Vector2d tableScreenDim = {tableScreenW, tableScreenH};
    Pos res = (drawPos * tableScreenDim / tableDim) + tableScreenPos;
    return {res.x, res.y};
}

SDL_Point Ball::screenPos() {
    Pos tableScreenPos = {tableScreenOffsetX, tableScreenOffsetY};
    Vector2d tableDim = {tableW, tableH};
    Vector2d tableScreenDim = {tableScreenW, tableScreenH};
    Pos res = (pos * tableScreenDim / tableDim) + tableScreenPos;
    return {res.x, res.y};   
}