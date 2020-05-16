//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#include <algorithm>
#include "Tetriminos/_all.h"
#include "MinoSet.h"

MinoSet::MinoSet() {
    index = 0;

    for (int i = minoI; i <= minoZ; i++) {
        rand[i - 1] = static_cast<MinoType>(i);
    }

    rng = std::mt19937(std::random_device()()); // Set random engine
    shuffle();
}

void MinoSet::shuffle() {
    std::shuffle(std::begin(rand), std::end(rand), rng);
    index = 0;
}

Tetrimino* MinoSet::get() {
    MinoType return_type = rand[index];
    if (index == 6) {
        shuffle();
        index = 0;
    } else index++;

    switch (return_type) {
        case minoI:
            return new Mino_I();
        case minoO:
            return new Mino_O();
        case minoT:
            return new Mino_T();
        case minoL:
            return new Mino_L();
        case minoJ:
            return new Mino_J();
        case minoS:
            return new Mino_S();
        case minoZ:
            return new Mino_Z();
        default:
            return nullptr;
    }

}