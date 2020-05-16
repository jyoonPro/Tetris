//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#ifndef ASSN3_TETRIMINO_H
#define ASSN3_TETRIMINO_H


#include "Block.h"
#include "enum.h"

class Tetrimino {
private:
    int x;
    int y;

protected:
    Block* blocks;
    int rotation;
    MinoType type;

    static int modulo(int i);

public:
    int getX() const;
    int getY() const;
    int getRotation() const;
    void setX(int _x);
    void setY(int y);
    void setXY(int x, int y);
    void shift(int dx, int dy);
    virtual void rotate(int dr) = 0;
    virtual void reset() = 0;

    const Block* getBlock(int i) const;
    MinoType getType() const;

    Tetrimino();
    virtual ~Tetrimino();
};


#endif //ASSN3_TETRIMINO_H
