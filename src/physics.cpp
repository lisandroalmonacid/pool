#include "physics.h"

void nextState(Ball* balls) {
    updateBalls(balls);
    manageCollisions(balls);
}


//UPDATE BALLS SECTION

void updateBalls(Ball* balls) {
    for (int i = 0; i < 16; i++) {
        updateBall(&balls[i]);
    }
}

void updateBall(Ball* b) {
	updateBallPosition(b);
    updateBallVelocity(b);
    manageBorderCollisions(b);
}


void updateBallPosition(Ball* b) {
    b->pos.x = b->pos.x + b->vel.x;
    b->pos.y = b->pos.y + b->vel.y;
}

void updateBallVelocity(Ball* b) {
    b->vel.x = applyFriction(b->vel.x);

    if (std::abs(b->vel.x) < minVelocity)
        b->vel.x = 0;

    b->vel.y = applyFriction(b->vel.y);

    if (std::abs(b->vel.y) < minVelocity)
        b->vel.y = 0;
}

float applyFriction(float vel) {
    if (vel > 0) {
        vel -= frictionEffect;
    } else if (vel < 0) {
        vel += frictionEffect;
    }
    return vel;
}

//If the ball went past the table edge, get it right in the edge and invert the velocity.
void manageBorderCollisions(Ball* b) {
    if (b->pos.x > tableRightBorder){
        b->pos.x = tableRightBorder;
        b->vel.x = -b->vel.x;
    }
    if (b->pos.x < tableLeftBorder) {
        b->pos.x = tableLeftBorder;
        b->vel.x = -b->vel.x;
    }
    if (b->pos.y > tableDownBorder){
        b->pos.y = tableDownBorder;
        b->vel.y = -b->vel.y;
    }
    if (b->pos.y < tableUpBorder) {
        b->pos.y = tableUpBorder;
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
    if (isMoving(b1) && isMoving(b2)) {
        movingCollision(b1, b2);
    } else if (isMoving(b1)) {
        stationaryCollision(b1, b2);
    } else if (isMoving(b2)) {
        stationaryCollision(b2, b1);
    }
}



bool ballsAreColliding(Ball* b1, Ball* b2){
	float dist_x = b1->pos.x - b2->pos.x;
    float dist_y = b1->pos.y - b2->pos.y;

    float norm = sqrt(pow(dist_x, 2) + pow(dist_y, 2));

    return norm <= (2 * ballRadius);
}


void movingCollision(Ball* b1, Ball* b2) {
    float _impactAngle = impactAngle(b1, b2);
    
    float v1 = velocityNorm(b1);
    float v2 = velocityNorm(b2);

    float a1 = movementAngle(b1);
    float a2 = movementAngle(b2);

    float v1_new_x = v2 * cos (a2 - _impactAngle) * cos(_impactAngle) + v1 * sin(a1 - _impactAngle) * cos(_impactAngle + pi/2);
    float v1_new_y = v2 * cos (a2 - _impactAngle) * sin(_impactAngle) + v1 * sin(a1 - _impactAngle) * sin(_impactAngle + pi/2);

    float v2_new_x = v1 * cos (a1 - _impactAngle) * cos(_impactAngle) + v2 * sin(a2 - _impactAngle) * cos(_impactAngle + pi/2);
    float v2_new_y = v1 * cos (a1 - _impactAngle) * sin(_impactAngle) + v2 * sin(a2 - _impactAngle) * sin(_impactAngle + pi/2);

    b1->vel.x = v1_new_x; b1->vel.y = v1_new_y;
    b2->vel.x = v2_new_x; b2->vel.y = v2_new_y;
    
    setBallsApart(b1, b2);
}

void stationaryCollision(Ball* b1, Ball* b2) {
    float _impactAngle = impactAngle(b1, b2);

    float v1_new = velocityNorm(b1) * sqrt((1 + cos(_impactAngle))/2);
    float v2_new = velocityNorm(b1) * sin(_impactAngle / 2);

    float v1_newAngle = _impactAngle + pi/2;
    float v2_newAngle = _impactAngle;

    float v1_new_x = v1_new * cos(v1_newAngle);
    float v1_new_y = v1_new * sin(v1_newAngle);

    float v2_new_x = v2_new * cos(v2_newAngle);
    float v2_new_y = v2_new * sin(v2_newAngle);

    b1->vel.x = v1_new_x; b1->vel.y = v1_new_y;
    b2->vel.x = v2_new_x; b2->vel.y = v2_new_y;

    setBallsApart(b1, b2);
}

float impactAngle(Ball* b1, Ball* b2) {
    float dist_x = b1->pos.x - b2->pos.x;
    float dist_y = b1->pos.y - b2->pos.y;
    float impactAngle = atan(dist_y/dist_x);
    
    //adjust angle orientation
    if (b1->vel.x < 0 && b1->vel.y >= 0) {
        impactAngle += pi/2;
    } else if (b1->vel.x < 0 && b1->vel.y < 0) {
        impactAngle += pi;
    } else if (b1->vel.x > 0 && b1->vel.y < 0) {
        impactAngle -= pi/2;
    }
    //get it inside interval (0, 2pi)
    return fmod(impactAngle + 2*pi, 2*pi);
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

    for (int i = 0; !res && i < 16; i++) {
        res = isMoving(&balls[i]);
    }
    return res;
}

float velocityNorm(Ball* b) {
    return sqrt(pow(b->vel.x, 2) + pow(b->vel.y, 2));
}

float movementAngle(Ball* b) {
    return fmod(atan(b->vel.y/b->vel.x) + 2*pi, 2*pi);
}

bool isMoving(Ball* b) {
    return b->vel.x != 0 || b->vel.y != 0;
}