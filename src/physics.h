#ifndef PHYSICS_H
#define PHYSICS_H

#include "types.h"
#include "defines.h"
#include "Ball.h"



//manage collisions
void manageBallCollisions(Ball* balls, Ball* b);
void manageCollision(Ball* b1, Ball* b2);
bool ballsAreColliding(Ball* b1, Ball* b2);
void ballCollision(Ball* b1, Ball* b2);
void movingCollision(Ball* b1, Ball* b2);
void stationaryCollision(Ball* b1, Ball* b2);
void manageBorderCollisions(Ball* b);
bool isBallCollidingWithWall(Ball* b, Pos p1, Pos p2);

//aux
float impactAngle(Ball* b1, Ball* b2);
bool ballsMoving(Ball* balls);
void setBallsApart(Ball* b1, Ball* b2);
float pointsNorm(Pos p1, Pos p2);
Vel findUnitNormalVector(Pos p1, Pos p2);
Pos intersection(Dir v1, Pos p1, Dir v2, Pos p2);
bool isPointInLine(Pos p, Pos l1, Pos l2);

#endif