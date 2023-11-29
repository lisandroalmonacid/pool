//
// Created by li_al on 28/11/2023.
//

#ifndef POOL_SCENE_H
#define POOL_SCENE_H

class Scene {
public:
    virtual bool init();
    virtual bool loop();
    virtual bool exit();
};


#endif //POOL_SCENE_H
