//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#include "Mino_S.h"

// Constructors

Mino_S::Mino_S() {
    rotation = 0;
    type = minoS;

    setXY(init_x, init_y);
    setRotation(rotation);

    for (int i = 0; i < 4; i++) {
        blocks[i].setColor(GREEN);
    }
}

Mino_S::Mino_S(int _x, int _y, int _rotation) {
    rotation = _rotation;
    type = minoS;

    setXY(_x, _y);
    setRotation(_rotation);

    for (int i = 0; i < 4; i++) {
        blocks[i].setColor(GREEN);
    }
}

// Function Definitions

void Mino_S::reset() {
    rotation = 0;
    setXY(init_x, init_y);
    setRotation(rotation);
}

void Mino_S::setRotation(int r) {
    // Get data from position and update block positions
    for (int i = 0; i < 4; i++) {
        int rel_x = position[r][i] % 3;
        int rel_y = position[r][i] / 3;
        blocks[i].setRelXY(rel_x, rel_y);
    }
}

void Mino_S::rotate(int dr) {
    // Get positive modulo
    rotation = modulo(rotation + dr);
    setRotation(rotation);
}