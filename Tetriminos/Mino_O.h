//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#ifndef ASSN3_MINO_O_H
#define ASSN3_MINO_O_H


#include "../Tetrimino.h"

class Mino_O: public Tetrimino {
private:
    static const int init_x;
    static const int init_y;
    void setBlocks();

public:
    void rotate(int dr) override;
    void reset() override;

    Mino_O();
    Mino_O(int x, int y);
};


#endif //ASSN3_MINO_O_H
