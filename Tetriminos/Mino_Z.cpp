//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#include "Mino_Z.h"

// Constructors

Mino_Z::Mino_Z() {
    rotation = 0;
    type = minoZ;

    setXY(init_x, init_y);
    setRotation(rotation);

    for (int i = 0; i < 4; i++) {
        blocks[i].setColor(RED);
    }
}

Mino_Z::Mino_Z(int _x, int _y, int _rotation) {
    rotation = _rotation;
    type = minoZ;

    setXY(_x, _y);
    setRotation(_rotation);

    for (int i = 0; i < 4; i++) {
        blocks[i].setColor(RED);
    }
}

// Function Definitions

void Mino_Z::reset() {
    rotation = 0;
    setXY(init_x, init_y);
    setRotation(rotation);
}

void Mino_Z::setRotation(int r) {
    // Get data from position and update block positions
    for (int i = 0; i < 4; i++) {
        int rel_x = position[r][i] % 3;
        int rel_y = position[r][i] / 3;
        blocks[i].setRelXY(rel_x, rel_y);
    }
}

void Mino_Z::rotate(int dr) {
    // Get positive modulo
    rotation = modulo(rotation + dr);
    setRotation(rotation);
}