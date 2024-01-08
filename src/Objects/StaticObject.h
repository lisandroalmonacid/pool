//
// Created by li_al on 8/1/2024.
//

#ifndef POOL_STATICOBJECT_H
#define POOL_STATICOBJECT_H

#include "GameObject.h"
#include "../Texture.h"

class StaticObject : public GameObject {
public:
    void draw() override;
    StaticObject(int x, int y, Texture* texture);

private:
    Texture* _texture;
    int _x;
    int _y;
};


#endif //POOL_STATICOBJECT_H
