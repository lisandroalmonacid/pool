#ifndef GAME_H
#define GAME_H

#include "physics.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <queue>
#include "Ball.h"
#include "TextBox.h"

class Game {
public:
  Game();
  void mainMenuScreen();
  void gameScreen();
  void gameLoop();

  void nextTurn();
  void switchPlayer();
  void restoreCueBall();
  bool anyBallsIn(BallClass bClass);
  void displayTurnMessages();
  void displayClassMessages();

  void aimLoop();
  void executeShot();

  void start();
  void finish(bool winner);
  void quitGame();

  void updateBalls();
  void manageBallCollisions();
  void manageBorderCollisions(Ball* b);
  bool ballsMoving();
  bool areAllBallsIn();
  void processEventQueue();
  void render();

private:
  bool KEYS[322];  // 322 is the number of SDLK_DOWN events
  int mouseX;
  int mouseY;
  bool mouseClick;

  int shotForce;

  Action action;
  
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

  std::queue<TextBox*> messageQueue;
};

#endif