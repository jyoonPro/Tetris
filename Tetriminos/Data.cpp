//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//

#include "../constant.h"
#include "Mino_I.h"
#include "Mino_O.h"
#include "Mino_T.h"
#include "Mino_L.h"
#include "Mino_J.h"
#include "Mino_S.h"
#include "Mino_Z.h"


// Initial Position Data

const int Mino_I::init_x = FIELD_WIDTH / 2 - 2;
const int Mino_I::init_y = -1;

const int Mino_O::init_x = FIELD_WIDTH / 2 - 1;
const int Mino_O::init_y = 0;

const int Mino_T::init_x = FIELD_WIDTH / 2 - 2;
const int Mino_T::init_y = 0;

const int Mino_L::init_x = FIELD_WIDTH / 2 - 2;
const int Mino_L::init_y = 0;

const int Mino_J::init_x = FIELD_WIDTH / 2 - 2;
const int Mino_J::init_y = 0;

const int Mino_S::init_x = FIELD_WIDTH / 2 - 2;
const int Mino_S::init_y = 0;

const int Mino_Z::init_x = FIELD_WIDTH / 2 - 2;
const int Mino_Z::init_y = 0;



// Rotation Data

const int Mino_I::position[4][4] {
        {4, 5, 6, 7},
        {2, 6, 10, 14},
        {8, 9, 10, 11},
        {1, 5, 9, 13}
};

const int Mino_T::position[4][4] {
        {1, 3, 4, 5},
        {1, 4, 5, 7},
        {3, 4, 5, 7},
        {1, 3, 4, 7}
};

const int Mino_L::position[4][4] {
        {2, 3, 4, 5},
        {1, 4, 7, 8},
        {3, 4, 5, 6},
        {0, 1, 4, 7}
};

const int Mino_J::position[4][4] {
        {0, 3, 4, 5},
        {1, 2, 4, 7},
        {3, 4, 5, 8},
        {1, 4, 6, 7}
};

const int Mino_S::position[4][4] {
        {1, 2, 3, 4},
        {1, 4, 5, 8},
        {4, 5, 6, 7},
        {0, 3, 4, 7}
};

const int Mino_Z::position[4][4] {
        {0, 1, 4, 5},
        {2, 4, 5, 7},
        {3, 4, 7, 8},
        {1, 3, 4, 6}
};