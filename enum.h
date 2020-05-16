//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#ifndef ASSN3_ENUM_H
#define ASSN3_ENUM_H

enum Color {
    WHITE,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
};

enum MinoType {
    UNDEFINED,
    minoI,
    minoO,
    minoT,
    minoL,
    minoJ,
    minoS,
    minoZ,
};

enum Keystroke {
    NONE,
    keyA,
    keyD,
    keyS,
    keyW,
    keyC,
    keyX,
    keyM,
    SPACE,
};

enum Moves {
    INVALID,
    VALID,
    T_SPIN_MINI,
    T_SPIN,
};

#endif //ASSN3_ENUM_H
