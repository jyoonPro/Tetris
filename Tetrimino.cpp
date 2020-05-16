//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#include "Tetrimino.h"

// Constructor and Destructor
Tetrimino::Tetrimino() {
    x = 0;
    y = 0;
    rotation = 0;
    type = UNDEFINED;
    blocks = new Block[4];
}

Tetrimino::~Tetrimino() {
    delete[] blocks;
}

int Tetrimino::getX() const { return x; }
int Tetrimino::getY() const { return y; }
int Tetrimino::getRotation() const { return rotation; }
MinoType Tetrimino::getType() const { return type; }
const Block* Tetrimino::getBlock(int i) const { return blocks + i; }

void Tetrimino::setX(int _x) { x = _x; }
void Tetrimino::setY(int _y) { y = _y; }
void Tetrimino::setXY(int _x, int _y) { x = _x; y = _y; }
void Tetrimino::shift(int dx, int dy) { x += dx; y += dy; }

int Tetrimino::modulo(int i) {
    return (i % 4 + 4) % 4;
}
