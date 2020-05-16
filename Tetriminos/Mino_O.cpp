//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#include "Mino_O.h"

// Constructors

Mino_O::Mino_O() {
    rotation = 0;
    type = minoO;

    setXY(init_x, init_y);
    setBlocks();

    for (int i = 0; i < 4; i++) {
        blocks[i].setColor(YELLOW);
    }
}

Mino_O::Mino_O(int _x, int _y) {
    rotation = 0;
    type = minoO;

    setXY(_x, _y);
    setBlocks();

    for (int i = 0; i < 4; i++) {
        blocks[i].setColor(YELLOW);
    }
}

// Function Definitions

void Mino_O::reset() {
    setXY(init_x, init_y);
}

void Mino_O::setBlocks() {
    // There is only 1 possible combination
    blocks[0].setRelXY(0, 0);
    blocks[1].setRelXY(1, 0);
    blocks[2].setRelXY(0, 1);
    blocks[3].setRelXY(1, 1);
}

void Mino_O::rotate(int dr) {
    // Do nothing
}
