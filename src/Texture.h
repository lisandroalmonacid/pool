#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "types.h"

class Texture {
public:
    Texture(SDL_Renderer* rend);
    ~Texture();

    bool loadFromFile(const char* filepath);

    bool loadFromText(const char* text, TTF_Font* font, SDL_Color color);

    void draw(Pos screenPos);
    void setBlendMode();
    void setAlpha();
    void setAngle(double newAngle);
    void freeTexture();

//private:
    SDL_Texture* _texture;
    int _w;
    int _h;
    SDL_Rect* _srcRect;
    double _angle;
    bool _usesRotation;

    SDL_Renderer* _rend;

};

#endif