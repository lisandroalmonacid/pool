#ifndef PHYSICS_H
#define PHYSICS_H

#include "types.h"
#include "defines.h"

void nextState(Ball* balls);

//update balls
void updateBalls(Ball* balls);
void updateBall(Ball* b);
void updateBallPosition(Ball* b);
void updateBallVelocity(Ball* b);

//manage collisions
void manageCollisions(Ball* balls);
void manageCollision(Ball* b1, Ball* b2);
bool ballsAreColliding(Ball* b1, Ball* b2);
void ballCollision(Ball* b1, Ball* b2);
void movingCollision(Ball* b1, Ball* b2);
void stationaryCollision(Ball* b1, Ball* b2);
void manageBorderCollisions(Ball* b);

//aux
float impactAngle(Ball* b1, Ball* b2);
bool ballsMoving(Ball* balls);
float applyFriction(float vel);
void setBallsApart(Ball* b1, Ball* b2);
float velocityNorm(Ball* b);
float movementAngle(Ball* b);
bool isMoving(Ball* b);

#endif