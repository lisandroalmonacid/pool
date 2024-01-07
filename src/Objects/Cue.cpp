//
// Created by li_al on 29/11/2023.
//

#include "Cue.h"

Cue::Cue(Texture *cueTexture, Ball *cueBall) : _texture(cueTexture), _cueBall(cueBall) {}

Cue::~Cue() {}

void Cue::draw(int shotForce) {
    Pos mousePos =  {(gameState.mouseX - tableScreenOffsetX)/tableScreenW*tableW, (gameState.mouseY - tableScreenOffsetY)/tableScreenH*tableH};
    double cueAngle = angleBetweenPoints(_cueBall->pos, mousePos);
    _texture->_angle = cueAngle * 180 / M_PI;
    //std::cout << "angle: " << _texture->_angle << std::endl;

    double x = ((cueW + 2*ballRadius + cueBallSpace + shotForce*4) * cosf(cueAngle) + cueW)/2;
    double y = ((cueW + 2*ballRadius + cueBallSpace + shotForce*4) * sinf(cueAngle) + cueH)/2;
    double cueX = _cueBall->pos.x - x;
    double cueY = _cueBall->pos.y - y;

    _texture->_w = cueW * tableScreenW / tableW;
    _texture->_h = cueH * tableScreenH / tableH;

    _texture->draw({
                           (int) cueX*tableScreenW/tableW + tableScreenOffsetX,
                           (int) cueY*tableScreenH/tableH + tableScreenOffsetY
                   });

    //drawBallTrajectory(balls, mouseX, cueAngle);
}
