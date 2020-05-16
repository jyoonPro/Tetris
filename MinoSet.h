//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#ifndef ASSN3_MINOSET_H
#define ASSN3_MINOSET_H


#include <random>
#include "enum.h"
#include "Tetrimino.h"

class MinoSet {
private:
    MinoType rand[7];
    std::mt19937 rng;
    int index;

public:
    Tetrimino* get();
    void shuffle();

    MinoSet();
};


#endif //ASSN3_MINOSET_H
