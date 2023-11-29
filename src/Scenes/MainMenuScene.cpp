//
// Created by li_al on 28/11/2023.
//

#include "MainMenuScene.h"

bool MainMenuScene::init() {
    title = new TextBox(0, {screenW/2, screenH/2}, false, true);
    subtitle = new TextBox(1, {screenW/2, screenH/2 + 200}, true, true);
}
bool MainMenuScene::loop() {
    title->draw(0, 0);
    subtitle->draw(mouseX, mouseY);
    SDL_RenderPresent(rend);
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);

    if (mouseClick) {
        if (subtitle->isHovered(mouseX, mouseY)) {
            return false;
        }
        mouseClick = false;
    }
    return true;
}

bool MainMenuScene::exit() {

}