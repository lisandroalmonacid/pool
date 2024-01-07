#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "GameObject.h"
#include "../Texture.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "../types.h"
#include "../globals.h"

class TextBox : public GameObject {
public:
  TextBox(int messageNumber, Pos screenPos, bool bordered, bool centered);
  ~TextBox();
  void draw() override;
  bool isHovered();
  int ttl;

private:  
  Texture* _texture;
  Pos _screenPos;
  bool _bordered;
  bool _hovered;
  bool _clicked;
};

#endif