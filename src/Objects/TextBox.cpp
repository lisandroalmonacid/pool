#include "TextBox.h"

TextBox::TextBox(int messageNumber, Pos screenPos, bool bordered, bool centered) {
    _texture = messageTextures[messageNumber];
    _screenPos = screenPos;
    _bordered = bordered;
    _hovered = true;
    _clicked = false;
    if (centered) {
        _screenPos = {_screenPos.x - _texture->_w, _screenPos.y - _texture->_h};
    }
    ttl = 100;
}


TextBox::~TextBox() {
    _texture = nullptr;
}

void TextBox::draw() {
    SDL_Rect dstRect = {(int) _screenPos.x, (int) _screenPos.y, _texture->_w, _texture->_h};

    if (isHovered()) {
        SDL_SetRenderDrawColor(rend, 255, 255, 0, 100);
        SDL_RenderFillRect(rend, &dstRect);
    }

    if (_bordered) {
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        SDL_RenderDrawRect(rend, &dstRect);
    }
    _texture->draw(_screenPos);
}

bool TextBox::isHovered() {
    return (_screenPos.x <= gameState.mouseX) && (_screenPos.x + _texture->_w >= gameState.mouseX) &&
            (_screenPos.y <= gameState.mouseY) && (_screenPos.y + _texture->_h >= gameState.mouseY);
}