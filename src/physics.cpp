#include "physics.h"
#include "SDLAux.h"
#include <iostream>


//UPDATE BALLS SECTION

void updateBalls(Ball* balls) {
    for (int i = 0; i < 16; i++) {
        balls[i].update();
        manageBorderCollisions(&balls[i]);
    }
}

void manageBorderCollisions(Ball* b) {
    for (int i = 1; i < 24; i++) {
        if (isBallCollidingWithWall(b, tableEdges[i-1], tableEdges[i])) {
            SDL_SetRenderDrawColor(rend, 255, 0, 0, 0);
            SDL_RenderDrawLine(rend, tableEdges[i-1].x, tableEdges[i-1].y, tableEdges[i].x, tableEdges[i].y);
            SDL_Rect rect = {b->pos.x - ballRadius, b->pos.y - ballRadius, ballRadius*2,ballRadius*2};
            SDL_RenderDrawRect(rend, &rect);
            SDL_RenderPresent(rend);
            SDL_Delay(50);
            SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
            SDL_RenderClear(rend);
            Vel n = findUnitNormalVector(tableEdges[i-1], tableEdges[i]);
            //b->vel = b->vel - 2 * (b->vel * n) * n. Consider adding vector operators. 
            float vDotN = b->vel.x * n.x + b->vel.y + n.y;
            b->vel = {b->vel.x - 2*vDotN * n.x, b->vel.y - 2*vDotN * n.y};
        }
    }
}

Vel findUnitNormalVector(Pos p1, Pos p2) {
    if (p1.x == p2.x) return {1, 0};
    if (p1.y == p2.y) return {0, 1};

    float m = (p2.y - p1.y)/(p2.x-p1.x);
    float mOrt = -1/m;
    float norm = sqrt(1+mOrt*mOrt);
    return {1/norm, mOrt/norm};
}

bool isBallCollidingWithWall (Ball* b, Pos p1, Pos p2) {
    //obtener dirección de la recta que pasa por v1, v2
    Dir wallDir = {p2.x - p1.x, p2.y - p1.y};

    //obtener dirección ortogonal a la recta
    Dir ortDir;
    if (wallDir.y == 0) ortDir = {0, 1};
    else if (wallDir.x == 0) ortDir = {1, 0};
    else ortDir = {1, -wallDir.x/wallDir.y};

    Pos iPos = intersection(wallDir, p1, ortDir, b->pos);

    Pos closestPoint;
    if ( isPointInLine(iPos, p1, p2) ) {
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

Pos intersection(Dir v1, Pos p1, Dir v2, Pos p2) {
    if (v1.x == 0 || v1.y*v2.x == v2.y ) return {p1};
    float k2 = (p2.y - p1.y - v1.y*(p2.x - p1.x)/v1.x) / (-v2.y + v1.y*v2.x/v1.x);
    return {k2*v2.x + p2.x, k2*v2.y + p2.y};
}

//MANAGE COLLISIONS
void manageCollisions(Ball* balls) {
    for (int i = 0; i < 16; i++) {
        for (int j = i + 1; j < 16; j++){
            if (ballsAreColliding(&balls[i], &balls[j]))
                manageCollision(&balls[i], &balls[j]);
        }
    }
}

void manageCollision(Ball* b1, Ball* b2) {
    if (b1->isMoving() && b2->isMoving()) {
        movingCollision(b1, b2);
    } else if (b1->isMoving()) {
        stationaryCollision(b1, b2);
    } else if (b2->isMoving()) {
        stationaryCollision(b2, b1);
    }
}

bool isColliding(Ball* balls, Ball* ball) {
    //is colliding with other balls
    for (int i = 1; i < 16; i++) {
        if (ballsAreColliding(&balls[i], ball)) {
            return true;
        }
    }

    //is colliding with borders
    if (ball->pos.x <= tableLeftBorder || ball->pos.y <= tableUpBorder ||
        ball->pos.x >= tableRightBorder || ball->pos.y >= tableDownBorder)
        return true;

    return false;
}


bool ballsAreColliding(Ball* b1, Ball* b2){
    if (b1->isIn || b2->isIn) return false;

	float dist_x = b1->pos.x - b2->pos.x;
    float dist_y = b1->pos.y - b2->pos.y;

    float norm = sqrt(pow(dist_x, 2) + pow(dist_y, 2));

    return norm <= (2 * ballRadius);
}

float pointsNorm(Pos p1, Pos p2) {
    float dist_x = p1.x - p2.x;
    float dist_y = p1.y - p2.y;

    return sqrt(pow(dist_x, 2) + pow(dist_y, 2));
}

void movingCollision(Ball* b1, Ball* b2) {
    float iAngle = impactAngle(b1, b2);
    
    float v1 = b1->velocityNorm();
    float v2 = b2->velocityNorm();

    float a1 = b1->movementAngle();
    float a2 = b2->movementAngle();

    float v1NewX = v2 * cos(a2 - iAngle) * cos(iAngle) + v1 * sin(a1 - iAngle) * cos(iAngle + M_PI/2);
    float v1NewY = v2 * cos(a2 - iAngle) * sin(iAngle) + v1 * sin(a1 - iAngle) * sin(iAngle + M_PI/2);

    float v2NewX = v1 * cos(a1 - iAngle) * cos(iAngle) + v2 * sin(a2 - iAngle) * cos(iAngle + M_PI/2);
    float v2NewY = v1 * cos(a1 - iAngle) * sin(iAngle) + v2 * sin(a2 - iAngle) * sin(iAngle + M_PI/2);

    b1->vel.x = v1NewX; b1->vel.y = v1NewY;
    b2->vel.x = v2NewX; b2->vel.y = v2NewY;
    
    setBallsApart(b1, b2);
}

void stationaryCollision(Ball* b1, Ball* b2) {
    float iAngle = impactAngle(b1, b2);

    float v1_new = b1->velocityNorm() * sqrt((1 + cos(iAngle))/2);
    float v2_new = b1->velocityNorm() * sin(iAngle / 2);

    float v1_newAngle = iAngle + M_PI/2;
    float v2_newAngle = iAngle;

    float v1NewX = v1_new * cos(v1_newAngle);
    float v1NewY = v1_new * sin(v1_newAngle);

    float v2NewX = v2_new * cos(v2_newAngle);
    float v2NewY = v2_new * sin(v2_newAngle);

    b1->vel.x = v1NewX; b1->vel.y = v1NewY;
    b2->vel.x = v2NewX; b2->vel.y = v2NewY;

    setBallsApart(b1, b2);
}

float impactAngle(Ball* b1, Ball* b2) {
    float dist_x = b1->pos.x - b2->pos.x;
    float dist_y = b1->pos.y - b2->pos.y;
    float impactAngle = atan(dist_y/dist_x);
    
    //adjust angle orientation
    if (b1->vel.x < 0 && b1->vel.y >= 0) {
        impactAngle += M_PI/2;
    } else if (b1->vel.x < 0 && b1->vel.y < 0) {
        impactAngle += M_PI;
    } else if (b1->vel.x > 0 && b1->vel.y < 0) {
        impactAngle -= M_PI/2;
    }
    //get it inside interval (0, 2pi)
    return fmod(impactAngle + 2*M_PI, 2*M_PI);
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


//AUX
bool ballsMoving(Ball* balls) {
    bool res = false;

    for (int i = 0; !res && i < 16; i++)
        res = balls[i].isMoving();

    return res;
}