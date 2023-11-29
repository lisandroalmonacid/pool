//
// Created by li_al on 28/11/2023.
//

#ifndef POOL_MAINMENUSCENE_H
#define POOL_MAINMENUSCENE_H

#include "Scene.h"
#include "../TextBox.h"
#include "../defines.h"

class MainMenuScene : Scene {
    bool init();
    bool loop();
    bool exit();

    TextBox* title;
    TextBox* subtitle;
};


#endif //POOL_MAINMENUSCENE_H
