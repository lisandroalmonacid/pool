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
#include "Scene.h"

class PoolScene : public Scene {

    std::vector<Ball*> balls;
    Ball* cueBall;
    Ball* eightBall;

    Player players[2];

    bool curPlayer; //0 = player 1; 1 = player 2.
    bool ballInHand;

    bool aimMode;

    Ball* firstTouchedBall;
    Ball* firstPocketedBall;

    std::queue<TextBox*> messageQueue;

    bool init();
    Action loop();
    bool exit();
    void render() override;

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

    bool areAllBallsIn();

    void finish(bool winner);

public:
    bool ballsMoving();

    bool ballInHandMode;
    int shotForce;
};


#endif //POOL_POOLSCENE_H
