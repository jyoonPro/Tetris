//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#ifndef ASSN3_TETRIS_H
#define ASSN3_TETRIS_H


#include "ConsoleEngine.h"
#include "Playfield.h"
#include "MinoSet.h"
#include "Score.h"

class Tetris: public ConsoleEngine {
private:
    Playfield field;
    MinoSet set;
    Score score;
    int cleared_row;
    int combo;
    int b2b;
    Moves last_move;
    Keystroke last_key;
    bool hold_used;

    double speed_multiplier;
    bool is_shadowed;
    bool is_break;

    Tetrimino* mino_current;
    Tetrimino* mino_next;
    Tetrimino* mino_hold;
    Tetrimino* mino_shadow;

    std::thread async_drop;
    bool reset_drop_timer{};

    void dropPiece();
    void clearLines();
    void asyncDropPiece();
    void animateGameOver();
    void project(Tetrimino* t);
    void newShadow();

protected:
    void slice();

public:
    void startRound();
    void doAction(Keystroke key);
    bool isGameOver();
    void gameOverMenu();
    void restart();

    Tetris();
    ~Tetris();
};


#endif //ASSN3_TETRIS_H
