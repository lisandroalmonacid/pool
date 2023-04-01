#include "physics.h"


//UPDATE BALLS SECTION

void updateBalls(Ball* balls) {
    for (int i = 0; i < 16; i++) {
        balls[i].update();
        manageBorderCollisions(&balls[i]);
    }
}

//If the ball went past the table edge, get it right in the edge and invert the velocity.
void manageBorderCollisions(Ball* b) {
    if (b->isIn) return;

    if (b->pos.x > tableRightBorder - ballRadius){
        b->pos.x = tableRightBorder - ballRadius;
        b->vel.x = -b->vel.x;
    }
    if (b->pos.x < tableLeftBorder + ballRadius) {
        b->pos.x = tableLeftBorder + ballRadius;
        b->vel.x = -b->vel.x;
    }
    if (b->pos.y > tableDownBorder - ballRadius){
        b->pos.y = tableDownBorder - ballRadius;
        b->vel.y = -b->vel.y;
    }
    if (b->pos.y < tableUpBorder + ballRadius) {
        b->pos.y = tableUpBorder + ballRadius;
        b->vel.y = -b->vel.y;
    }
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