//
// Created by li_al on 29/11/2023.
//

#ifndef POOL_TABLE_H
#define POOL_TABLE_H

#include "../Texture.h"
#include "GameObject.h"
#include "../globals.h"

class Table : public GameObject {
public:
    Table(Texture* tableTexture);
    ~Table();
    void draw() override;
private:
    Texture* _texture;
};


#endif //POOL_TABLE_H
