//
// Created by li_al on 29/11/2023.
//

#ifndef POOL_MESSAGEBOX_H
#define POOL_MESSAGEBOX_H

#include "GameObject.h"
#include "../Texture.h"
#include "../globals.h"
#include "TextBox.h"
#include <queue>

class MessageBox : public GameObject {
public:
    MessageBox(std::queue<TextBox*> messageQueue);
    ~MessageBox();
    void draw() override;
private:
    std::queue<TextBox*> _messageQueue;
};


#endif //POOL_MESSAGEBOX_H
