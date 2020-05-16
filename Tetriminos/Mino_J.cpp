//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#include "Mino_J.h"

// Constructors

Mino_J::Mino_J() {
    rotation = 0;
    type = minoJ;

    setXY(init_x, init_y);
    setRotation(rotation);

    for (int i = 0; i < 4; i++) {
        blocks[i].setColor(BLUE);
    }
}

Mino_J::Mino_J(int _x, int _y, int _rotation) {
    rotation = _rotation;
    type = minoJ;

    setXY(_x, _y);
    setRotation(_rotation);

    for (int i = 0; i < 4; i++) {
        blocks[i].setColor(BLUE);
    }
}

// Function Definitions
void Mino_J::reset() {
    rotation = 0;
    setXY(init_x, init_y);
    setRotation(rotation);
}

void Mino_J::setRotation(int r) {
    // Get data from position and update block positions
    for (int i = 0; i < 4; i++) {
        int rel_x = position[r][i] % 3;
        int rel_y = position[r][i] / 3;
        blocks[i].setRelXY(rel_x, rel_y);
    }
}

void Mino_J::rotate(int dr) {
    // Get positive modulo
    rotation = modulo(rotation + dr);
    setRotation(rotation);
}
