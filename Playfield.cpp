//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#include "Playfield.h"
#include "constant.h"
#include "Tetriminos/_all.h"

// Constructor and Destructor

Playfield::Playfield() {
    field = new Block**[FIELD_HEIGHT];
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        field[i] = new Block*[FIELD_WIDTH];
    }

    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            field[i][j] = nullptr;
        }
    }
}

Playfield::~Playfield() {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (field[i][j] != nullptr) delete field[i][j];
        }
        delete[] field[i];
    }
    delete[] field;
}

// Function Definitions
const Block* Playfield::getBlock(int x, int y) const {
    return field[y][x];
}

bool Playfield::checkFree(int x, int y) {
    // Return true if free
    // Out of bounds blocks are not free
    if (x < 0 || x >= FIELD_WIDTH || y < 0 || y >= FIELD_HEIGHT) return false;
    return field[y][x] == nullptr;
}

bool Playfield::checkFit(const Tetrimino *t, int dx, int dy) {
    // Return true if the piece fits
    int origin_x = t->getX() + dx;
    int origin_y = t->getY() + dy;

    for (int i = 0; i < 4; i++) {
        int x = origin_x + t->getBlock(i)->getRelX();
        int y = origin_y + t->getBlock(i)->getRelY();
        if (!checkFree(x, y)) return false;
    }

    return true;
}

bool Playfield::checkRow(int r) {
    // Return true if the row is full
    for (int i = 0; i < FIELD_WIDTH; i++) {
        if (field[r][i] == nullptr) return false;
    }

    return true;
}

void Playfield::deleteRow(int r) {
    // First delete current row objects
    for (int i = 0; i < FIELD_WIDTH; i++) {
        if (field[r][i] != nullptr) delete field[r][i];
    }

    // Move all top rows one block down
    for (int i = r; i > 0; i--) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            field[i][j] = field[i - 1][j];
        }
    }

    // Fill top row with nullptr
    for (int i = 0; i < FIELD_WIDTH; i++) {
        field[0][i] = nullptr;
    }
}

Moves Playfield::isValid(const Tetrimino *t, int& dx, int& dy, int dr) {
    // Checks if shift, rotation movement is valid
    // Checks for walls, wall kick, and T-spin movements
    // input dx is 1 or -1 / dy is 1 / dr is 1 or -1
    // xy shift and rotation are not simultaneous inputs
    Tetrimino *temp = nullptr;
    Moves return_val = INVALID;
    int orig_x = t->getX();
    int orig_y = t->getY();
    int orig_r = t->getRotation();

    // Set rotation case
    int param1, final_r = orig_r;
    if (dr != 0) {
        if (orig_r == 0) {
            if      (dr ==  1) { param1 = 0; final_r = 1; }
            else if (dr == -1) { param1 = 7; final_r = 3; }
        } else if (orig_r == 1) {
            if      (dr ==  1) { param1 = 2; final_r = 2; }
            else if (dr == -1) { param1 = 1; final_r = 0; }
        } else if (orig_r == 2) {
            if      (dr ==  1) { param1 = 4; final_r = 3; }
            else if (dr == -1) { param1 = 3; final_r = 1; }
        } else if (orig_r == 3) {
            if      (dr ==  1) { param1 = 6; final_r = 0; }
            else if (dr == -1) { param1 = 5; final_r = 2; }
        }
    }

    if (t->getType() == minoO) {
        // Check bounds
        if (checkFit(t, dx, dy)) return VALID;
        else return INVALID;
    }
    else {
        if (dr == 0) {
            // Check bounds
            if (checkFit(t, dx, dy)) return VALID;
            else return INVALID;
        } else { // dx and dy are initially 0
            int param3 = 0;
            bool check_tspin = false;

            // Check MinoType
            if (t->getType() == minoI) {
                param3 = 1;
                temp = new Mino_I(orig_x, orig_y, final_r);
            }
            else if (t->getType() == minoL) temp = new Mino_L(orig_x, orig_y, final_r);
            else if (t->getType() == minoJ) temp = new Mino_J(orig_x, orig_y, final_r);
            else if (t->getType() == minoS) temp = new Mino_S(orig_x, orig_y, final_r);
            else if (t->getType() == minoZ) temp = new Mino_Z(orig_x, orig_y, final_r);
            else if (t->getType() == minoT) {
                check_tspin = true;
                temp = new Mino_T(orig_x, orig_y, final_r);
            }

            // Perform 5 tests
            if (checkFit(temp)) {
                return_val = VALID;
            } else if (checkFit(temp, wk_data[param1][0][param3][0], wk_data[param1][0][param3][1])) {
                dx = wk_data[param1][0][param3][0];
                dy = wk_data[param1][0][param3][1];
                return_val = VALID;
            } else if (checkFit(temp, wk_data[param1][1][param3][0], wk_data[param1][1][param3][1])) {
                dx = wk_data[param1][1][param3][0];
                dy = wk_data[param1][1][param3][1];
                return_val = VALID;
            } else if (checkFit(temp, wk_data[param1][2][param3][0], wk_data[param1][2][param3][1])) {
                dx = wk_data[param1][2][param3][0];
                dy = wk_data[param1][2][param3][1];
                return_val = VALID;
            } else if (checkFit(temp, wk_data[param1][3][param3][0], wk_data[param1][3][param3][1])) {
                dx = wk_data[param1][3][param3][0];
                dy = wk_data[param1][3][param3][1];
                return_val = VALID;
            }

            // Check for T-Spin
            if (return_val == VALID && check_tspin) {
                // Check 3 corners
                int occupied_corners = 0;
                if (!checkFree(orig_x + dx, orig_y + dy)) occupied_corners++;
                if (!checkFree(orig_x + dx + 2, orig_y + dy)) occupied_corners++;
                if (!checkFree(orig_x + dx, orig_y + dy + 2)) occupied_corners++;
                if (!checkFree(orig_x + dx + 2, orig_y + dy + 2)) occupied_corners++;

                if (occupied_corners >= 3) {
                    // R/L -> 0: Mini
                    if (param1 == 1 || param1 == 6) {
                        return_val = T_SPIN_MINI;
                    }
                    // R/L -> 2: Single
                    else if (param1 == 2 || param1 == 5) {
                        return_val = T_SPIN;
                    }
                    // 2 -> R/L: Mini if Single
                    else if (param1 == 3 || param1 == 4) {
                        return_val = T_SPIN_MINI;
                    }
                    // 0 -> R/L: If roof exists, Single
                    else {
                        if (!checkFree(orig_x, orig_y) || !checkFree(orig_x + 2, orig_y)) {
                            return_val = T_SPIN;
                        } else {
                            return_val = T_SPIN_MINI;
                        }
                    }
                }
            }

            delete temp;
            return return_val;
        }
    }
}

void Playfield::fixPosition(const Tetrimino *t) {
    // Store current tetrimino into playfield
    int orig_x = t->getX();
    int orig_y = t->getY();

    for (int i = 0; i < 4; i++) {
        auto* temp = new Block(*(t->getBlock(i)));
        field[orig_y + temp->getRelY()][orig_x + temp->getRelX()] = temp;
    }
}

bool Playfield::isGameOver() {
    for (int i = 0; i < FIELD_WIDTH; i++) {
        if (field[0][i] != nullptr) return true;
    }
    return false;
}

void Playfield::reset() {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (field[i][j] != nullptr) {
                delete field[i][j];
                field[i][j] = nullptr;
            }
        }
    }
}

void Playfield::fillRed(int r) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
        if (field[r][j] != nullptr) {
            field[r][j]->setColor(RED);
        } else {
            field[r][j] = new Block(0, 0, RED);
        }
    }
}


/* Wall Kick Data
 * From the official documentation
 * 1st param: 0 (0 -> R)
 *            1 (R -> 0)
 *            2 (R -> 2)
 *            3 (2 -> R)
 *            4 (2 -> L)
 *            5 (L -> 2)
 *            6 (L -> 0)
 *            7 (0 -> L)
 *
 * 2nd param: 0 (Test 2)
 *            1 (Test 3)
 *            2 (Test 4)
 *            3 (Test 5)
 *
 * 3rd param: 0 (J, L, S, T, Z Tetrimino)
 *            1 (I Tetrimino)
 *
 * 4th param: 0 (dx)
 *            1 (dy)
 */

int Playfield::wk_data[8][4][2][2] {
        {
                {{-1,  0}, {-2,  0}},
                {{-1, -1}, { 1,  0}},
                {{ 0,  2}, {-2,  1}},
                {{-1,  2}, { 1, -2}},
        },
        {
                {{ 1,  0}, { 2,  0}},
                {{ 1,  1}, {-1,  0}},
                {{ 0, -2}, { 2, -1}},
                {{ 1, -2}, {-1,  2}},
        },
        {
                {{ 1,  0}, {-1,  0}},
                {{ 1,  1}, { 2,  0}},
                {{ 0, -2}, {-1, -2}},
                {{ 1, -2}, { 2,  1}},
        },
        {
                {{-1,  0}, { 1,  0}},
                {{-1, -1}, {-2,  0}},
                {{ 0,  2}, { 1,  2}},
                {{-1,  2}, {-2, -1}},
        },
        {
                {{ 1,  0}, { 2,  0}},
                {{ 1, -1}, {-1,  0}},
                {{ 0,  2}, { 2, -1}},
                {{ 1,  2}, {-1,  2}},
        },
        {
                {{-1,  0}, {-2,  0}},
                {{-1,  1}, { 1,  0}},
                {{ 0, -2}, {-2,  1}},
                {{-1, -2}, { 1, -2}},
        },
        {
                {{-1,  0}, { 1,  0}},
                {{-1,  1}, {-2,  0}},
                {{ 0, -2}, { 1,  2}},
                {{-1, -2}, {-2, -1}},
        },
        {
                {{ 1,  0}, {-1,  0}},
                {{ 1, -1}, { 2,  0}},
                {{ 0,  2}, {-1, -2}},
                {{ 1,  2}, { 2,  1}},
        },
};