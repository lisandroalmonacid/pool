//
// Created by li_al on 29/11/2023.
//

#ifndef POOL_CUE_H
#define POOL_CUE_H

#include "GameObject.h"
#include "../Texture.h"
#include "../globals.h"
#include "Ball.h"
#include "../physics.h"

class Cue : public GameObject {
public:
    Cue(Texture* cueTexture, Ball* cueBall);
    ~Cue();
    void draw() override;
private:
    Texture* _texture;
    Ball* _cueBall;
};


#endif //POOL_CUE_H
