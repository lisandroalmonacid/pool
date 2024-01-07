//
// Created by li_al on 28/11/2023.
//

#include "MainMenuScene.h"

bool MainMenuScene::init() {
    std::cout << "Entering main menu" << std::endl;
    title = new TextBox(0, screenMiddle, false, true);
    subtitle = new TextBox(1, {screenW/2, screenH/2 + 200}, true, true);
    objects.push_back(title);
    objects.push_back(subtitle);
}

Action MainMenuScene::loop() {
    if (gameState.mouseClick) {
        if (subtitle->isHovered()) {
            return Pool;
        }
        gameState.mouseClick = false;
    }
    return MainMenu;
}

bool MainMenuScene::exit() {
    std::cout << "Exiting main menu" << std::endl;
}