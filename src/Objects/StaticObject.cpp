//
// Created by li_al on 8/1/2024.
//

#include "StaticObject.h"

StaticObject::StaticObject(int x, int y, Texture *texture) {
    _x = x;
    _y = y;
    _texture = texture;
}

void StaticObject::draw() {
    _texture->draw({_x, _y});
}