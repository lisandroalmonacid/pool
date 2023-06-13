#include "Texture.h"
#include <iostream>

Texture::Texture(SDL_Renderer* rend) : _rend(rend), _usesRotation(false) {
    _texture = nullptr;
    _srcRect = nullptr;
    _angle = 0;
}

Texture::~Texture() {
    freeTexture();
}

bool Texture::loadFromFile(const char* filepath) {
    if (_texture != nullptr)
        this->freeTexture();

    _texture = IMG_LoadTexture(_rend, filepath);
    SDL_QueryTexture(_texture, NULL, NULL, &_w, &_h);
    
    return true;
}

bool Texture::loadFromText(const char* text, TTF_Font* font, SDL_Color color) {
    if (_texture != nullptr)
        this->freeTexture();

    SDL_Surface* tmp = TTF_RenderText_Solid(font, text, color);
    _texture = SDL_CreateTextureFromSurface(_rend, tmp);
    SDL_FreeSurface(tmp);
    tmp = nullptr;
    SDL_QueryTexture(_texture, NULL, NULL, &_w, &_h);

    return true;
}

void Texture::draw(SDL_Point screenPos) {
    SDL_Rect dstRect = {screenPos.x, screenPos.y, _w, _h};
    if (_usesRotation) {
        SDL_RenderCopyEx(_rend, _texture, _srcRect, &dstRect, _angle, nullptr, SDL_FLIP_HORIZONTAL);
    } else {
        SDL_RenderCopy(_rend, _texture, _srcRect, &dstRect);
    }
}

void Texture::setBlendMode() {}

void Texture::setAlpha() {}

void Texture::setAngle(float newAngle) {
    _angle = newAngle;
}

void Texture::freeTexture() {
    if (_texture != nullptr) {
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
    }

    if (_srcRect != nullptr) {
        delete _srcRect;
        _srcRect = nullptr;
    }
}