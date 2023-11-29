#ifndef PHYSICS_H
#define PHYSICS_H

#include "types.h"
#include "globals.h"
#include "Objects/Ball.h"
#include <vector>



//manage collisions
bool ballsAreColliding(Ball* b1, Ball* b2);
void ballCollision(Ball* b1, Ball* b2);
void borderCollision(Ball* b, Pos l1, Pos l2);
bool isBallCollidingWithWall(Ball* b, Pos p1, Pos p2);
std::pair<int, double> closestWall(Ball* b);
double distanceToWall(Ball* b, Pos p1, Pos p2);

//aux
double angleBetweenPoints(Pos p1, Pos p2);
void setBallsApart(Ball* b1, Ball* b2);
double pointsNorm(Pos p1, Pos p2);
Vel findUnitNormalVector(Pos p1, Pos p2);
Pos intersection(Vector2d v1, Pos p1, Vector2d v2, Pos p2);
bool isPointInLine(Pos p, Pos l1, Pos l2);
bool inBounds(Ball* b);

#endif