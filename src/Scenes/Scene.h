//
// Created by li_al on 28/11/2023.
//

#ifndef POOL_SCENE_H
#define POOL_SCENE_H

#include <vector>
#include "../types.h"
#include "../Objects/GameObject.h"

class Scene {
public:
    virtual bool init() {return true;};
    virtual Action loop() {return MainMenu;};
    virtual bool exit() {return true;};

    virtual void render() {
        for (GameObject* object : objects) {
            object->draw();
        }
    };

    std::vector<GameObject*> objects;
};


#endif //POOL_SCENE_H
