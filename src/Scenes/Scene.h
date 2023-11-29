//
// Created by li_al on 28/11/2023.
//

#ifndef POOL_SCENE_H
#define POOL_SCENE_H

#include <vector>

class Scene {
public:
    virtual bool init();
    virtual Action loop();
    virtual bool exit();

    virtual void render() {
        for (GameObject* object : objects) {
            object->draw();
        }
    };

    std::vector<GameObject*> objects;




};


#endif //POOL_SCENE_H
