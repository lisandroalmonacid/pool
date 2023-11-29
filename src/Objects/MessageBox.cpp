//
// Created by li_al on 29/11/2023.
//

#include "MessageBox.h"

MessageBox::MessageBox(std::queue<TextBox *> messageQueue) : _messageQueue(messageQueue) {}

MessageBox::~MessageBox() {}

void MessageBox::draw() {
    if (_messageQueue.size() > 0) {
        _messageQueue.front()->draw();
        _messageQueue.front()->ttl--;
        if (_messageQueue.front()->ttl == 0) _messageQueue.pop();
    }
}
