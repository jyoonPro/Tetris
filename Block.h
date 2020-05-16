//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#ifndef ASSN3_BLOCK_H
#define ASSN3_BLOCK_H

#include "enum.h"

class Block {
private:
    int rel_x;
    int rel_y;
    Color color;

public:
    int getRelX() const;
    int getRelY() const;
    void setRelX(int x);
    void setRelY(int y);
    void setRelXY(int x, int y);
    void shift(int dx, int dy);

    Color getColor() const;
    void setColor(Color c);

    Block();
    Block(int rel_x, int rel_y, Color c);
};


#endif //ASSN3_BLOCK_H
