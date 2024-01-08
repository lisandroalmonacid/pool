//
// Created by li_al on 28/11/2023.
//

#ifndef POOL_MAINMENUSCENE_H
#define POOL_MAINMENUSCENE_H

#include "Scene.h"
#include "../Objects/TextBox.h"
#include "../globals.h"
#include "../Objects/StaticObject.h"

class MainMenuScene : public Scene {
    bool init() override;
    Action loop() override;
    bool exit() override;

    StaticObject* title;
    StaticObject* subtitle;
};


#endif //POOL_MAINMENUSCENE_H
