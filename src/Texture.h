#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Texture {
public:
    Texture(SDL_Renderer* rend);
    ~Texture();

    bool loadFromFile(const char* filepath);

    bool loadFromText(const char* text, TTF_Font* font, SDL_Color color);

    void draw(SDL_Point screenPos);
    void setBlendMode();
    void setAlpha();
    void setAngle(float newAngle);
    void freeTexture();

//private:
    SDL_Texture* _texture;
    int _w;
    int _h;
    SDL_Rect* _srcRect;
    float _angle;
    bool _usesRotation;

    SDL_Renderer* _rend;

};

#endif