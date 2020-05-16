//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#include "Block.h"

// Constructors
Block::Block() {
    rel_x = 0;
    rel_y = 0;
    color = WHITE;
}

Block::Block(int rel_x, int rel_y, Color c) {
    this->rel_x = rel_x;
    this->rel_y = rel_y;
    color = c;
}

// Function definition

int Block::getRelX() const { return rel_x; }
int Block::getRelY() const { return rel_y; }
Color Block::getColor() const { return color; }

void Block::setRelX(int x) { rel_x = x; }
void Block::setRelY(int y) { rel_y = y; }
void Block::setRelXY(int x, int y) { rel_x = x; rel_y = y; }
void Block::shift(int dx, int dy) { rel_x += dx; rel_y += dy; }

void Block::setColor(Color c) { color = c; }
