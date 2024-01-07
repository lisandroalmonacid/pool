//
// Created by li_al on 28/11/2023.
//

#include "PoolScene.h"

bool PoolScene::init() {
    std::cout << "Entering Pool" << std::endl;
    shotForce = 0;

    for (int i = 0; i < 16; i++) {
        Ball* b = new Ball(startingPositions[i], i);
        balls.push_back(b);
        objects.push_back(b);
    }
    cueBall = balls[0];
    eightBall = balls[8];

    cue = new Cue(cueTexture, cueBall);
    objects.push_back(cue);

    table = new Table(tableTexture);
    objects.push_back(table);

    // init players with correct ID and no ball class.
    players[0] = {0, None};
    players[1] = {1, None};

    curPlayer = 0; //0 = player 1; 1 = player 2.
    ballInHand = false;

    ballInHandMode = false;
    aimMode = false;

    firstTouchedBall = nullptr;
    poolAction = Aim;

    //displayTurnMessages();
}
Action PoolScene::loop() {
    switch (poolAction) {
        case Aim: {
            aimLoop();
            break;
        }
        case Shoot: {
            executeShot();
            break;
        }
        case NextTurn: {
            nextTurn();
            break;
        }
    }
    return Pool;
}

bool PoolScene::exit() {
    for (int i = 0; i < balls.size(); i++) {
        delete(balls[i]);
    }
}

void PoolScene::switchPlayer() {
    curPlayer = !curPlayer;
}

void PoolScene::restoreCueBall() {
    cueBall->isIn = false;
    cueBall->pos = startingPositions[0];
    cueBall->vel = {0, 0};
}

void PoolScene::nextTurn() {
    ballInHand = false;
    poolAction = Aim;

    if (firstTouchedBall == nullptr) {
        if (cueBall->isIn) restoreCueBall();
        switchPlayer();
        ballInHand = true;
        displayTurnMessages();
        return;
    }

    if (eightBall->isIn) {
        if (areAllBallsIn())
            finish(curPlayer);
        else
            finish(!curPlayer);
        return;
    }

    if (cueBall->isIn) {
        restoreCueBall();
        switchPlayer();
        ballInHand = true;
        displayTurnMessages();
        firstTouchedBall = nullptr;
        firstPocketedBall = nullptr;
        return;
    }

    if (players[curPlayer]._ballClass == None && firstPocketedBall != nullptr) {
        players[curPlayer]._ballClass = firstPocketedBall->_class;
        players[!curPlayer]._ballClass = firstPocketedBall->_class == Solid ? Striped : Solid;
        displayClassMessages();
        displayTurnMessages();
        firstTouchedBall = nullptr;
        firstPocketedBall = nullptr;
        return;
    }

    if (players[curPlayer]._ballClass != firstTouchedBall->_class) {
        switchPlayer();
        ballInHand = true;
        displayTurnMessages();
        firstTouchedBall = nullptr;
        firstPocketedBall = nullptr;
        return;
    }

    if (firstPocketedBall == nullptr || firstPocketedBall->_class != players[curPlayer]._ballClass) {
        switchPlayer();
        displayTurnMessages();
        firstTouchedBall = nullptr;
        firstPocketedBall = nullptr;
        return;
    }
    if (firstPocketedBall->_class == players[curPlayer]._ballClass) {
        displayTurnMessages();
        firstTouchedBall = nullptr;
        firstPocketedBall = nullptr;
        return;
    }
}

void PoolScene::displayClassMessages() {
    int p1MsgNbr = players[0]._ballClass == Solid ? 6 : 8;
    int p2MsgNbr = players[1]._ballClass == Solid ? 7 : 9;

    TextBox* p1Msg = new TextBox(p1MsgNbr, screenMiddle, false, true);
    TextBox* p2Msg = new TextBox(p2MsgNbr, screenMiddle, false, true);

    messageQueue.push(p1Msg);
    messageQueue.push(p2Msg);
}

void PoolScene::displayTurnMessages() {
    TextBox* turnMsg = nullptr;
    TextBox* ballInHandMsg = nullptr;

    if (curPlayer == 0) {
        turnMsg = new TextBox(2, screenMiddle, false, true);
        if (ballInHand) ballInHandMsg = new TextBox(4, screenMiddle, false, true);
    } else {
        turnMsg = new TextBox(3, screenMiddle, false, true);
        if (ballInHand) ballInHandMsg = new TextBox(5, screenMiddle, false, true);
    }

    messageQueue.push(turnMsg);
    if (ballInHand) messageQueue.push(ballInHandMsg);
}

bool PoolScene::anyBallsIn(BallClass bClass) {
    int l = bClass == Solid ? 1 : 9;
    int h = bClass == Solid ? 7 : 15;

    bool res;
    for (int i = l; i < h; i++)
        res = res || balls[i]->isIn;

    return res;
}

void PoolScene::aimLoop() {
    if (gameState.mouseClick) {
        Pos mousePos = {(gameState.mouseX - tableScreenOffsetX)/tableScreenW*tableW, (gameState.mouseY - tableScreenOffsetY)/tableScreenH*tableH};
        if ( ((mousePos - cueBall->pos).norm() < ballRadius || ballInHandMode) && !aimMode && ballInHand) {
            ballInHandMode = true;
            cueBall->pos = mousePos;
            shotForce = 0;
        } else if (shotForce < 25 && !ballInHandMode) {
            aimMode = true;
            shotForce = shotForce + 2;
            double cueAngle = angleBetweenPoints({cueBall->screenPos().x, cueBall->screenPos().y}, {gameState.mouseX, gameState.mouseY});
        }
    } else {
        ballInHandMode = false;
        aimMode = false;

        double cueAngle = angleBetweenPoints({cueBall->screenPos().x, cueBall->screenPos().y}, {gameState.mouseX, gameState.mouseY});
        cueBall->vel.x = shotForce * cos(cueAngle);
        cueBall->vel.y = shotForce * sin(cueAngle);
        shotForce = 0;

        if (ballsMoving()) poolAction = Shoot;
    }
}

void PoolScene::executeShot() {
    updateBalls();
    manageBallCollisions();

    if (!ballsMoving()) poolAction = NextTurn;
}

void PoolScene::updateBalls() {
    for (int i = 0; i < balls.size(); i++) {
        if (balls[i]->isMoving()) {
            balls[i]->update();
            manageBorderCollisions(balls[i]);
            if (balls[i]->isIn && firstPocketedBall == nullptr)
                firstPocketedBall = balls[i];
        }
    }
}

void PoolScene::manageBallCollisions() {
    for (int i = 0; i < balls.size(); i++) {
        for (int j = i + 1; j < balls.size(); j++){
            if (ballsAreColliding(balls[i], balls[j])) {
                ballCollision(balls[i], balls[j]);
                if (i == 0 && firstTouchedBall == nullptr) {
                    firstTouchedBall = balls[j];
                }
            }
        }
    }
}

void PoolScene::manageBorderCollisions(Ball* b) {
    if (inBounds(b)) {
        b->isCollidingWithWall = false;
        return;
    }
    //get closest wall to b, and its distance
    std::pair<int, double> cWall = closestWall(b);

    if (cWall.second < ballRadius) {
        if (cWall.first % 4 == 0) {
            b->isIn = true;
            b->pos = inPositions[b->number];
            b->vel = {0, 0};
        } else if (!(b->isCollidingWithWall)) {
            b->isCollidingWithWall = true;
            borderCollision(b, tableEdges[cWall.first-1], tableEdges[cWall.first]);
        }
    } else {
        b->isCollidingWithWall = false;
    }
}

bool PoolScene::ballsMoving() {
    bool res = false;

    for (int i = 0; !res && i < balls.size(); i++)
        res = balls[i]->isMoving();

    return res;
}

bool PoolScene::areAllBallsIn() {
    bool res = true;

    for (int i = 0; res && i < balls.size(); i++)
        res = balls[i]->isIn;

    return res;
}

void PoolScene::finish(bool winner) {
    TextBox* winMsg = winner ? new TextBox(10, screenMiddle, false, true) : new TextBox(11, screenMiddle, false, true);
    tableTexture->draw({tableScreenOffsetX, tableScreenOffsetY});

    for (int i = 0; i < balls.size(); i++)
        balls[i]->draw();

    winMsg->draw();
    SDL_RenderPresent(rend);
    SDL_Delay(5000);
    gameState.action = Quit;
}

void PoolScene::render() {
    table->draw();
    for (Ball* ball : balls) {
        ball->draw();
    }
    if (poolAction == Aim && !ballInHandMode) {
        cue->draw(shotForce);
    }
    if (messageQueue.size() > 0) {
        messageQueue.front()->draw();
        messageQueue.front()->ttl--;
        if (messageQueue.front()->ttl == 0) messageQueue.pop();
    }
};