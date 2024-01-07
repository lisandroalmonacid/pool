#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Scenes/Scene.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/PoolScene.h"

class Game {
public:
  Game();

  void start();
  void quitGame();
  void render();
  void processEventQueue();
  void switchScenes(Scene* newScene);

private:

  MainMenuScene* mainMenuScene;
  PoolScene* poolScene;
  Scene* currentScene;
};

#endif