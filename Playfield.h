//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#ifndef ASSN3_PLAYFIELD_H
#define ASSN3_PLAYFIELD_H


#include "Block.h"
#include "Tetrimino.h"
#include "enum.h"

class Playfield {
private:
    Block*** field;
    static int wk_data[8][4][2][2];

    bool checkFree(int x, int y);
    bool checkFit(const Tetrimino* t, int dx = 0, int dy = 0);

public:
    Moves isValid(const Tetrimino* t, int& dx, int& dy, int dr);
    void fixPosition(const Tetrimino* t);
    void deleteRow(int r);
    bool checkRow(int r);
    bool isGameOver();
    void reset();
    void fillRed(int r);
    const Block* getBlock(int x, int y) const;

    Playfield();
    ~Playfield();
};


#endif //ASSN3_PLAYFIELD_H
