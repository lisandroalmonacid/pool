//
// Created by li_al on 28/11/2023.
//

#ifndef POOL_POOLSCENE_H
#define POOL_POOLSCENE_H

#include "../physics.h"
#include <vector>
#include <queue>
#include "../Objects/Ball.h"
#include "../Objects/TextBox.h"

class PoolScene : public Scene {
    int shotForce;

    std::vector<Ball*> balls;
    Ball* cueBall;
    Ball* eightBall;

    Player players[2];

    bool curPlayer; //0 = player 1; 1 = player 2.
    bool ballInHand;

    bool ballInHandMode;
    bool aimMode;

    Ball* firstTouchedBall;
    Ball* firstPocketedBall;

    bool init();
    Action loop();
    bool exit();

    void nextTurn();
    void switchPlayer();
    void restoreCueBall();
    bool anyBallsIn(BallClass bClass);
    void displayTurnMessages();
    void displayClassMessages();

    void aimLoop();
    void executeShot();

    void updateBalls();
    void manageBallCollisions();
    void manageBorderCollisions(Ball* b);
    bool ballsMoving();
    bool areAllBallsIn();

    void finish(bool winner);
};


#endif //POOL_POOLSCENE_H
