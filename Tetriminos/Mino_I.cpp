//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#include "Mino_I.h"

// Constructors

Mino_I::Mino_I() {
    rotation = 0;
    type = minoI;

    setXY(init_x, init_y);
    setRotation(rotation);

    for (int i = 0; i < 4; i++) {
        blocks[i].setColor(CYAN);
    }
}

Mino_I::Mino_I(int _x, int _y, int _rotation) {
    rotation = _rotation;
    type = minoI;

    setXY(_x, _y);
    setRotation(_rotation);

    for (int i = 0; i < 4; i++) {
        blocks[i].setColor(CYAN);
    }
}

// Function Definitions
void Mino_I::reset() {
    rotation = 0;
    setXY(init_x, init_y);
    setRotation(rotation);
}

void Mino_I::setRotation(int r) {
    // Get data from position and update block positions
    for (int i = 0; i < 4; i++) {
        int rel_x = position[r][i] % 4;
        int rel_y = position[r][i] / 4;
        blocks[i].setRelXY(rel_x, rel_y);
    }
}

void Mino_I::rotate(int dr) {
    // Get positive modulo
    rotation = modulo(rotation + dr);
    setRotation(rotation);
}