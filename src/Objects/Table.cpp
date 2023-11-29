//
// Created by li_al on 29/11/2023.
//

#include "Table.h"

Table::Table(Texture *tableTexture) : _texture(tableTexture) {}

Table::~Table() {}

void Table::draw() {
    _texture->draw({
        (int) tableScreenOffsetX,
        (int) tableScreenOffsetY
    });
}