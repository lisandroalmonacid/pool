#ifndef PHYSICS_H
#define PHYSICS_H

#include "types.h"
#include "defines.h"
#include "Ball.h"



//manage collisions
void manageCollision(Ball* b1, Ball* b2);
bool ballsAreColliding(Ball* b1, Ball* b2);
void ballCollision(Ball* b1, Ball* b2);
void movingCollision(Ball* b1, Ball* b2);
void stationaryCollision(Ball* b1, Ball* b2);
void manageBorderCollisions(Ball* b);

//aux
float impactAngle(Ball* b1, Ball* b2);
bool ballsMoving(Ball* balls);
void setBallsApart(Ball* b1, Ball* b2);

#endif