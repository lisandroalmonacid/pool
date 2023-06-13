#include "Game.h"
#include <iostream>
#include "SDLAux.h"
#include <cmath>

Game::Game() {
    //Init KEYS
    for(int i = 0; i < 322; i++) {
        KEYS[i] = false;
    }
    mouseClick = false;
    shotForce = 0;
    action = MainMenu;

    for (int i = 0; i < 16; i++) {
	    Ball* b = new Ball(startingPositions[i], i);
        balls.push_back(b);
    }
    cueBall = balls[0];
    eightBall = balls[8];

    // init players with correct ID and no ball class.
    players[0] = {0, None};
    players[1] = {1, None};

    currPlayer = 0; //0 = player 1; 1 = player 2.
    ballInHand = false;

    ballInHandMode = false;
    aimMode = false;

    firstTouchedBall = nullptr;
}

void Game::start() {
    std::cout << "Starting game" << std::endl;
    while (action != Quit) {
        switch (action) {
        case MainMenu:
            mainMenuScreen();
            break;
        case game:
            gameLoop();
            break;
        default:
            break;
        }
    }
    quitGame();
    return;
}

void Game::mainMenuScreen() {
    std::cout << "Main menu!" << std::endl;
    TextBox* title = new TextBox(0, {screenW/2, screenH/2}, false, true);
    TextBox* subtitle = new TextBox(1, {screenW/2, screenH/2 + 200}, true, true);

    while(action == MainMenu) {
        processEventQueue();

        if (KEYS[SDLK_SPACE]) {
            KEYS[SDLK_SPACE] = false;
            action = game;
        }
        if (KEYS[SDLK_ESCAPE]) {
            KEYS[SDLK_ESCAPE] = false;
            action = Quit;
        }

        title->draw(0, 0);
        subtitle->draw(mouseX, mouseY);
        SDL_RenderPresent(rend);
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);

        if (mouseClick) {
            if (subtitle->isHovered(mouseX, mouseY)) {
                action = game;
            }
            mouseClick = false;
        }
    }

    std::cout << "Leaving main menu." << std::endl;
    return;
}

void Game::gameLoop() {
    while(action == game) {
        startTurn();
        aimLoop();
        executeShot();
        if (areAllBallsIn()) action = Quit;
    }
}

void Game::switchPlayer() {
    currPlayer = !currPlayer;
}

void Game::restoreCueBall() {
    cueBall->isIn = false;
    cueBall->pos = startingPositions[0];
    cueBall->vel = {0, 0};
}

void Game::startTurn() {
    ballInHand = false;

    if (firstTouchedBall == nullptr) {
        switchPlayer();
        displayTurnMessage();
        return;
    }

    if (eightBall->isIn) {
        finish(!currPlayer);
        return;
    }

    if (cueBall->isIn) {
        restoreCueBall();
        switchPlayer();
        ballInHand = true;
        displayTurnMessage();
        firstTouchedBall = nullptr;
        firstPocketedBall = nullptr;
        return;   
    }

    if (players[currPlayer]._ballClass == None && firstPocketedBall != nullptr) {
        players[currPlayer]._ballClass = firstPocketedBall->_class;
        players[!currPlayer]._ballClass = firstPocketedBall->_class == Solid ? Striped : Solid;
        displayTurnMessage();
        firstTouchedBall = nullptr;
        firstPocketedBall = nullptr;
        //class messages
        displayClassMessages();
        return;
    }

    if (players[currPlayer]._ballClass != firstTouchedBall->_class) {
        switchPlayer();
        ballInHand = true;
        displayTurnMessage();
        firstTouchedBall = nullptr;
        firstPocketedBall = nullptr;
        return;
    }

    if (!anyBallsIn(players[currPlayer]._ballClass)) {
        switchPlayer();
        displayTurnMessage();
        firstTouchedBall = nullptr;
        firstPocketedBall = nullptr;
        return;
    }
    if (anyBallsIn(players[currPlayer]._ballClass)) {
        displayTurnMessage();
        firstTouchedBall = nullptr;
        firstPocketedBall = nullptr;
        return;
    }

    return;
}

void Game::displayClassMessages() {
    int p1MsgNbr = players[0]._ballClass == Solid ? 6 : 8;
    int p2MsgNbr = players[1]._ballClass == Solid ? 7 : 9;

    TextBox* p1Msg = new TextBox(p1MsgNbr, screenMiddle, false, true);
    TextBox* p2Msg = new TextBox(p2MsgNbr, screenMiddle, false, true);

    messageQueue.push(p1Msg);
    messageQueue.push(p2Msg);
}

void Game::displayTurnMessage() {
    TextBox* turnMsg = nullptr;
    TextBox* ballInHandMsg = nullptr;

    if (currPlayer == 0) {
        turnMsg = new TextBox(2, screenMiddle, false, true);
        if (ballInHand) ballInHandMsg = new TextBox(4, screenMiddle, false, true);
    } else {
        turnMsg = new TextBox(3, screenMiddle, false, true);
        if (ballInHand) ballInHandMsg = new TextBox(5, screenMiddle, false, true);
    }

    messageQueue.push(turnMsg);
    if (ballInHand) messageQueue.push(ballInHandMsg);
}

bool Game::anyBallsIn(BallClass bClass) {
    int l = bClass == Solid ? 1 : 9;
    int h = bClass == Solid ? 7 : 15;

    bool res;
    for (int i = l; i < h; i++)
        res == res || balls[i]->isIn;
    
    return res;
}

void Game::aimLoop() {
    while (!ballsMoving() && action == game) {
        processEventQueue();
        if (mouseClick) {
            Pos mousePos = {(mouseX - tableScreenOffsetX)/tableScreenW*tableW, (mouseY - tableScreenOffsetY)/tableScreenH*tableH};
            if ( ((mousePos - cueBall->pos).norm() < ballRadius || ballInHandMode) && !aimMode && ballInHand) {
                ballInHandMode = true;
                cueBall->pos = mousePos;
                shotForce = 0;
            } else if (shotForce < 25 && !ballInHandMode) {
                aimMode = true;
                shotForce = shotForce + 2;
                float cueAngle = angleBetweenPoints({cueBall->screenPos().x, cueBall->screenPos().y}, {mouseX, mouseY});
            }
        } else {
            ballInHandMode = false;
            aimMode = false;

            float cueAngle = angleBetweenPoints({cueBall->screenPos().x, cueBall->screenPos().y}, {mouseX, mouseY});
            cueBall->vel.x = shotForce * cos(cueAngle);
            cueBall->vel.y = shotForce * sin(cueAngle);
            shotForce = 0;
        }
        render();
    }
}

void Game::executeShot() {
    while (ballsMoving() && action == game) {
        processEventQueue();
        updateBalls();
        manageBallCollisions();
        render();
    }
}

void Game::updateBalls() {
    for (int i = 0; i < balls.size(); i++) {
        if (balls[i]->isMoving()) {
            balls[i]->update();
            manageBorderCollisions(balls[i]);
            if (balls[i]->isIn && firstPocketedBall == nullptr)
                firstPocketedBall = balls[i];
        }
    }
}

void Game::manageBallCollisions() {
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

void Game::manageBorderCollisions(Ball* b) {
    if (inBounds(b)) {
        b->isCollidingWithWall = false;
        return;
    }
    //get closest wall to b, and its distance 
    std::pair<int, float> cWall = closestWall(b);

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

bool Game::ballsMoving() {
    bool res = false;

    for (int i = 0; !res && i < balls.size(); i++)
        res = balls[i]->isMoving();

    return res;
}

bool Game::areAllBallsIn() {
    bool res = true;

    for (int i = 0; res && i < balls.size(); i++)
        res = balls[i]->isIn;

    return res;    
}

void Game::processEventQueue() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            KEYS[event.key.keysym.sym] = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            mouseClick = true;
            break;
        case SDL_MOUSEBUTTONUP:
            mouseClick = false;
            break;
        case SDL_QUIT:
            action = Quit;
            break;
        default:
            break;
        }
    }

    SDL_GetMouseState(&mouseX, &mouseY);

    if (KEYS[SDLK_ESCAPE]) {
        KEYS[SDLK_ESCAPE] = false;
        action = Quit;
    }
    if (KEYS[SDLK_r]) {
        KEYS[SDLK_r] = false;
        action = MainMenu;
    }
}

void Game::render() {
    tableTexture->draw({(int)tableScreenOffsetX, (int)tableScreenOffsetY});
    for (int i = 0; i < balls.size(); i++)
        balls[i]->draw();

    if (!ballsMoving()) {
        //draw cue
        Pos mousePos =  {(mouseX - tableScreenOffsetX)/tableScreenW*tableW, (mouseY - tableScreenOffsetY)/tableScreenH*tableH};
        if (!ballInHandMode) {
            float cueAngle = angleBetweenPoints(cueBall->pos, mousePos);
            cueTexture->_angle = cueAngle * 180 / M_PI;
            //std::cout << "angle: " << cueTexture->_angle << std::endl; 

            float x = ((cueW + 2*ballRadius + cueBallSpace + shotForce*4) * cosf(cueAngle) + cueW)/2;
            float y = ((cueW + 2*ballRadius + cueBallSpace + shotForce*4) * sinf(cueAngle) + cueH)/2;
            float cueX = cueBall->pos.x - x;
            float cueY = cueBall->pos.y - y;

            cueTexture->_w = cueW*tableScreenW/tableW;
            cueTexture->_h = cueH*tableScreenH/tableH;
            cueTexture->draw({(int) cueX*tableScreenW/tableW + tableScreenOffsetX, 
                            (int) cueY*tableScreenH/tableH + tableScreenOffsetY});

            //drawBallTrajectory(balls, mouseX, cueAngle);
        }
    }

    if (messageQueue.size() > 0) {
        messageQueue.front()->draw(mouseX, mouseY);
        messageQueue.front()->ttl--;
        if (messageQueue.front()->ttl == 0) messageQueue.pop();
    }

    SDL_RenderPresent(rend);
    SDL_Delay(17);
    SDL_RenderClear(rend);
}

void Game::finish(int winner) {
	quitGame();
}

void Game::quitGame() {
    std::cout << "quitting!" << std::endl;
    for (int i = 0; i < balls.size(); i++) {
        delete(balls[i]);
    }
}