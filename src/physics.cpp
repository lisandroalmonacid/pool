#include "physics.h"
#include <iostream>
#include "SDLAux.h"

void borderCollision(Ball* b, Pos l1, Pos l2) {
    // drawCollision(b, l1, l2);
    Vel oldVel = b->vel;
    Vel n = findUnitNormalVector(l1, l2);
    b->vel = b->vel - n * (2 * (b->vel % n));
    b->pos -= oldVel;
}

Vel findUnitNormalVector(Pos p1, Pos p2) {
    if (p1.x == p2.x) return {1, 0};
    if (p1.y == p2.y) return {0, 1};

    return (Vector2d){1, -(p2.x-p1.x)/(p2.y - p1.y)}.unitVector();
}

bool isBallCollidingWithWall (Ball* b, Pos p1, Pos p2) {
    //obtener dirección de la recta que pasa por p1, p2
    Vector2d wallDir = p2 - p1;

    //obtener dirección ortogonal a la recta
    Vector2d ortDir;
    if (wallDir.y == 0) ortDir = {0, 1};
    else if (wallDir.x == 0) ortDir = {1, 0};
    else ortDir = {1, -wallDir.x/wallDir.y};

    Pos iPos = intersection(wallDir, p1, ortDir, b->pos);
    Pos closestPoint;
    if (isPointInLine(iPos, p1, p2)) {
        closestPoint = iPos;
    } else {
        closestPoint = pointsNorm(b->pos, p1) < pointsNorm(b->pos, p2) ? p1 : p2;
    }
    return (pointsNorm(b->pos, closestPoint) <= ballRadius);
}

bool isPointInLine(Pos p, Pos l1, Pos l2) {
    bool betweenX = ((l1.x <= p.x) && (p.x <= l2.x)) || ((l1.x >= p.x) && (p.x >= l2.x));
    bool betweenY = ((l1.y <= p.y) && (p.y <= l2.y)) || ((l1.y >= p.y) && (p.y >= l2.y));
    return betweenX && betweenY;
}

Pos intersection(Vector2d v1, Pos p1, Vector2d v2, Pos p2) {
    if (v1.x == 0) return {p1.x, p2.y}; // edge case: vertical lines.
    else if ( v1.y/v1.x == v2.y/v2.x ) return {-1, -1}; // edge case: parallel lines.

    float k2 = (p2.y - p1.y - v1.y*(p2.x - p1.x)/v1.x) / (-v2.y + v1.y*v2.x/v1.x);
    return {k2*v2.x + p2.x, k2*v2.y + p2.y};
}

bool ballsAreColliding(Ball* b1, Ball* b2) {
    return (b1->pos - b2->pos).norm() <= (2 * ballRadius);
}

float pointsNorm(Pos p1, Pos p2) {
    return (p1 - p2).norm();
}

void ballCollision(Ball* b1, Ball* b2) {
    Vector2d posDiff = b1->pos - b2->pos;
    Vector2d velDiff = b1->vel - b2->vel;
    b1->vel -= (posDiff) * ( (velDiff % posDiff) / posDiff.squareNorm() );

    posDiff = posDiff * -1;
    velDiff = velDiff * -1;
    b2->vel -= (posDiff) * ( (velDiff % posDiff) / posDiff.squareNorm() );

    //drawBallCollision(b1, b2);
    
    setBallsApart(b1, b2);
}

float angleBetweenPoints(Pos p1, Pos p2) {
    Pos diff = p1 - p2;
    float angle = atanf(diff.y/diff.x);
    
    if (diff.x < 0) angle += M_PI;

    return fmod(angle + 2*M_PI, 2*M_PI);
}

void setBallsApart(Ball* b1, Ball* b2) {
    while (ballsAreColliding(b1, b2)) {
        if (b1->pos.x > b2->pos.x) {    //b1 is to the right
            b1->pos.x = std::min(b1->pos.x + 1, tableRightBorder);
            b2->pos.x = std::max(b2->pos.x - 1, tableLeftBorder);
        } else {    //b1 is to the left
            b1->pos.x = std::max(b1->pos.x - 1, tableLeftBorder);
            b2->pos.x = std::min(b2->pos.x + 1, tableRightBorder);
        }

        if (b1->pos.y > b2->pos.y) {    //b1 is down
            b1->pos.y = std::min(b1->pos.y + 1, tableDownBorder);
            b2->pos.y = std::max(b2->pos.y - 1, tableUpBorder);
        } else {    //b1 is up
            b1->pos.y = std::max(b1->pos.y - 1, tableUpBorder);
            b2->pos.y = std::min(b2->pos.y + 1, tableDownBorder);
        }
    }
}

bool ballsMoving(std::vector<Ball*> balls) {
    bool res = false;

    for (int i = 0; !res && i < balls.size(); i++)
        res = balls[i]->isMoving();

    return res;
}