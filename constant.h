//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#ifndef ASSN3_CONSTANT_H
#define ASSN3_CONSTANT_H

// User configurable constants
// Note: Default terminal size is 80x24
#define FIELD_WIDTH  10
#define FIELD_HEIGHT 20
#define GAME_WIDTH   26
#define GAME_HEIGHT  22
#define FRAME_INT    20 // milliseconds (16)
#define BASE_SPEED   1500
#define SCORE_1      100 // = T Mini
#define SCORE_2      300
#define SCORE_3      500
#define SCORE_4      1000
#define T_SINGLE     500
#define T_DOUBLE     1000
#define T_TRIPLE     1500
#define B2B          200
#define COMBO        100
#define BLOCK_ICON   "■ "
#define WALL_ICON    "▦ "
#define SHADOW_ICON  "□ "
#define BLANK_STR    "  "
#define SCORESHEET   "score.txt"

// System specific constants
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#define cRED "\x1b[31m"
#define cGREEN "\x1b[32m"
#define cYELLOW "\x1b[33m"
#define cBLUE "\x1b[34m"
#define cMAGENTA "\x1b[35m"
#define cCYAN "\x1b[36m"
#define cWHITE "\x1b[37m"
#define cRESET "\x1b[0m"

#endif //ASSN3_CONSTANT_H
