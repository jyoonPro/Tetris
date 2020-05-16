//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#ifndef ASSN3_MINO_L_H
#define ASSN3_MINO_L_H


#include "../Tetrimino.h"

class Mino_L: public Tetrimino {
private:
    static const int init_x;
    static const int init_y;
    static const int position[4][4];
    void setRotation(int r);

public:
    void rotate(int dr) override;
    void reset() override;

    Mino_L();
    Mino_L(int x, int y, int rotation = 0);
};


#endif //ASSN3_MINO_L_H
