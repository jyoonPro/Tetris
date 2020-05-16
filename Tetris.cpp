//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#include <sstream>
#include "Tetris.h"
#include "Tetriminos/_all.h"
#include "constant.h"

// Constructor & Destructor
Tetris::Tetris() {
    combo = 0;
    b2b = 0;
    last_move = INVALID;
    last_key = NONE;
    cleared_row = 0;
    speed_multiplier = 1.0;
    is_shadowed = true;
    is_break = false;
    hold_used = false;
    reset_drop_timer = false;

    mino_current = nullptr;
    mino_next = nullptr;
    mino_hold = nullptr;
    mino_shadow = nullptr;
}

Tetris::~Tetris() {
    delete mino_current;
    delete mino_next;
    delete mino_hold;
    delete mino_shadow;
}

void Tetris::startRound() {
    // Initial set up
    mino_current = set.get();
    mino_next = set.get();
    if (is_shadowed) newShadow();

    // Start threads
    slice();
    start();
    async_drop = std::thread(&Tetris::asyncDropPiece, this);
    async_drop.detach();

    reset_drop_timer = true;
    is_break = false;
    hold_used = false;
    cleared_row = 0;

    while (!isGameOver() && !is_break) {
        // Main game loop

        // Execute user instruction
        getKey();
        if (curr_key) {
            if (curr_key != last_key) {
                doAction(curr_key);
                last_key = curr_key;
            }
        } else last_key = NONE;

        slice();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    delete mino_current;
    mino_current = nullptr;
    animateGameOver();
    stop();
    gameOverMenu();
}

void Tetris::clearLines() {
    // Only called when a piece is locked
    // and can check for combo

    int rows = 0;

    for (int i = 0; i < FIELD_HEIGHT; i++) {
        if (field.checkRow(i)) {
            reset_drop_timer = true;
            field.fillRed(i); // Animation purpose
            slice();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            field.deleteRow(i);
            rows++;
        }
    }
    cleared_row = rows;
    slice();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Determine score

    if (rows == 1) {
        if (last_move == T_SPIN_MINI) {
            score.add(SCORE_1);
            b2b++;
        }
        else if (last_move == T_SPIN) {
            score.add(T_SINGLE);
            b2b++;
        }
        else {
            score.add(SCORE_1);
            b2b = 0;
        }

        combo++;
    } else if (rows == 2) {
        if (last_move == T_SPIN_MINI || last_move == T_SPIN) {
            score.add(T_DOUBLE);
            b2b++;
        }
        else {
            score.add(SCORE_2);
            b2b = 0;
        }

        combo++;
    } else if (rows == 3) {
        if (last_move == T_SPIN_MINI || last_move == T_SPIN) {
            score.add(T_TRIPLE);
            b2b++;
        }
        else {
            score.add(SCORE_3);
            b2b = 0;
        }

        combo++;
    } else if (rows == 4) {
        score.add(SCORE_4);
        b2b++;
        combo++;
    } else {
        combo = 0; // Broken combo
    }

    // Apply b2b and combo bonus
    if (b2b >= 2) {
        score.add(B2B);
    }
    if (combo >= 2) {
        score.add(COMBO * (combo - 1));
    }

    // Adjust game speed every 1000 points
    int n = score.getScore() / 1000;
    if (n > 0) {
        speed_multiplier = 1.0;
        speed_multiplier += 0.1 * n;
    }
}

void Tetris::doAction(Keystroke key) {
    int dx = 0, dy = 0;

    switch (key) {
        case keyA: // Left
            dx = -1;
            if (field.isValid(mino_current, dx, dy, 0)) {
                mino_current->shift(dx, dy);

                if (is_shadowed) {
                    mino_shadow->setXY(mino_current->getX(), mino_current->getY());
                    project(mino_shadow);
                }
            }
            break;
        case keyD: // Right
            dx = 1;
            if (field.isValid(mino_current, dx, dy, 0)) {
                mino_current->shift(dx, dy);

                if (is_shadowed) {
                    mino_shadow->setXY(mino_current->getX(), mino_current->getY());
                    project(mino_shadow);
                }
            }
            break;
        case keyS: // Down
            reset_drop_timer = true;
            dropPiece();
            break;
        case keyW: // CW
            last_move = field.isValid(mino_current, dx, dy, 1);
            if (last_move) {
                mino_current->shift(dx, dy);
                mino_current->rotate(1);

                if (is_shadowed) {
                    mino_shadow->setXY(mino_current->getX(), mino_current->getY());
                    mino_shadow->rotate(1);
                    project(mino_shadow);
                }
            }
            break;
        case keyX: // CCW
            last_move = field.isValid(mino_current, dx, dy, -1);
            if (last_move) {
                mino_current->shift(dx, dy);
                mino_current->rotate(-1);

                if (is_shadowed) {
                    mino_shadow->setXY(mino_current->getX(), mino_current->getY());
                    mino_shadow->rotate(-1);
                    project(mino_shadow);
                }
            }
            break;
        case keyC: // Hold piece
            if (!hold_used) {
                reset_drop_timer = true;
                hold_used = true;
                if (mino_hold == nullptr) {
                    mino_hold = mino_current;
                    mino_hold->reset();
                    mino_current = mino_next;
                    mino_next = set.get();
                } else {
                    Tetrimino* temp = mino_current;
                    mino_current = mino_hold;
                    mino_hold = temp;
                    mino_hold->reset();
                }
                if (is_shadowed) {
                    delete mino_shadow;
                    newShadow();
                }
            }
            break;
        case keyM: // Shadow
            if (is_shadowed) {
                is_shadowed = false;
                delete mino_shadow;
            } else {
                is_shadowed = true;
                // Create new shadow
                newShadow();
            }
            break;
        case SPACE: // Hard drop
            reset_drop_timer = true;
            project(mino_current);
            dropPiece();
            break;
        default: /* Do nothing */;
    }
}

void Tetris::newShadow() {
    if (mino_current) {
        int x = mino_current->getX();
        int y = mino_current->getY();
        int r = mino_current->getRotation();
        // Create new object for shadow
        switch (mino_current->getType()) {
            case minoI:
                mino_shadow = new Mino_I(x, y, r);
                break;
            case minoO:
                mino_shadow = new Mino_O(x, y);
                break;
            case minoT:
                mino_shadow = new Mino_T(x, y, r);
                break;
            case minoL:
                mino_shadow = new Mino_L(x, y, r);
                break;
            case minoJ:
                mino_shadow = new Mino_J(x, y, r);
                break;
            case minoS:
                mino_shadow = new Mino_S(x, y, r);
                break;
            case minoZ:
                mino_shadow = new Mino_Z(x, y, r);
                break;
            default:
                is_shadowed = false; // Something went wrong
        }

        if (is_shadowed) project(mino_shadow);
    }
}

void Tetris::dropPiece() {
    if (mino_current) {
        // Shift y by 1, and fix position if the move is invalid
        int dx = 0, dy = 1;
        if (field.isValid(mino_current, dx, dy, 0)) {
            mino_current->shift(0, 1);
        } else {
            // Lock mino into position
            field.fixPosition(mino_current);
            delete mino_current;

            mino_current = mino_next;
            mino_next = set.get();
            hold_used = false;

            if (is_shadowed) {
                delete mino_shadow;
                newShadow();
            }

            clearLines();
            project(mino_shadow);
        }
    }
}

void Tetris::asyncDropPiece() {
    // Thread to drop pieces according to game speed

    while (is_running) {

        if (reset_drop_timer) {
            reset_drop_timer = false;
            continue;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(int(BASE_SPEED / speed_multiplier)));
        dropPiece();

        // Reset last move flag
        last_move = VALID;
    }
}

void Tetris::animateGameOver() {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        field.fillRed(i);
        slice();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Tetris::project(Tetrimino *t) {
    // Move the tetrimino to the bottom
    int dx = 0, dy = 1;
    while (field.isValid(t, dx, dy, 0)) {
        dy++;
    }
    if (dy != 1) t->shift(0, dy - 1);
}

void Tetris::slice() {
    // Generate the game frame
    pause = true;
    // The field

    for (int i = 1; i < 1 + FIELD_HEIGHT; i++) {
        for (int j = 8; j < 8 + FIELD_WIDTH; j++) {
            if (const Block* b = field.getBlock(j - 8, i - 1)) {
                frame_char[i][j] = BLOCK_ICON;
                frame_color[i][j] = b->getColor();
            } else {
                frame_char[i][j] = BLANK_STR;
                frame_color[i][j] = WHITE;
            }
        }
    }

    // Clear field for Hold, Next
    for (int i = 2; i <= 3; i++) {
        for (int j = 2; j <= 5; j++) {
            frame_char[i][j] = BLANK_STR;
        }
        for (int j = 10 + FIELD_WIDTH; j < GAME_WIDTH - 2; j++) {
            frame_char[i][j] = BLANK_STR;
        }
    }

    // Clear field for score
    for (int j = 4; j <= 5; j++) {
        frame_char[7][j] = "";
    }
    for (int j = 1; j <= 6; j++) {
        frame_char[8][j] = BLANK_STR;
    }
    for (int j = 10 + FIELD_WIDTH; j <= GAME_WIDTH - 3; j++) {
        frame_char[8][j] = "";
    }

    // Insert new values
    // Shadow

    if (mino_current) {
        Color curr_color = mino_current->getBlock(0)->getColor();

        if (is_shadowed && mino_shadow) {
            int shadow_abs_x = 8 + mino_shadow->getX();
            int shadow_abs_y = 1 + mino_shadow->getY();
            for (int i = 0; i < 4; i++) {
                int x = shadow_abs_x + mino_shadow->getBlock(i)->getRelX();
                int y = shadow_abs_y + mino_shadow->getBlock(i)->getRelY();
                frame_char[y][x] = SHADOW_ICON;
                frame_color[y][x] = curr_color;
            }
        }

        // Current
        int curr_abs_x = 8 + mino_current->getX();
        int curr_abs_y = 1 + mino_current->getY();
        for (int i = 0; i < 4; i++) {
            int x = curr_abs_x + mino_current->getBlock(i)->getRelX();
            int y = curr_abs_y + mino_current->getBlock(i)->getRelY();
            frame_char[y][x] = BLOCK_ICON;
            frame_color[y][x] = curr_color;
        }
    }

    // Hold
    if (mino_hold) {
        Color hold_color = mino_hold->getBlock(0)->getColor();
        for (int i = 0; i < 4; i++) {
            int x = 2 + mino_hold->getBlock(i)->getRelX();
            int y = 2 + mino_hold->getBlock(i)->getRelY();
            frame_char[y][x] = BLOCK_ICON;
            frame_color[y][x] = hold_color;
        }
    }

    // Next
    Color next_color = mino_next->getBlock(0)->getColor();
    for (int i = 0; i < 4; i++) {
        int x = 10 + FIELD_WIDTH + mino_next->getBlock(i)->getRelX();
        int y = 2 + mino_next->getBlock(i)->getRelY();
        frame_char[y][x] = BLOCK_ICON;
        frame_color[y][x] = next_color;
    }

    // Combo & score
    if (b2b >= 2) { // Back to back
        frame_char[7][4] = "B2B!";
    } else {
        char temp_combo[5];
        sprintf(temp_combo, "%4d", combo);
        frame_char[7][4] = std::string(temp_combo);
    }

    int curr_score = score.getScore();
    char temp_score[9];
    sprintf(temp_score, "%8d", curr_score);
    frame_char[8][10 + FIELD_WIDTH] = std::string(temp_score);

    if (cleared_row == 1) {
        if (last_move == T_SPIN_MINI) {
            frame_char[8][1] = "T ";
            frame_char[8][2] = "Sp";
            frame_char[8][3] = "in";
            frame_char[8][4] = " M";
            frame_char[8][5] = "in";
            frame_char[8][6] = "i!";
        } else if (last_move == T_SPIN) {
            frame_char[8][2] = "T ";
            frame_char[8][3] = "Sp";
            frame_char[8][4] = "in";
            frame_char[8][5] = "! ";
        }
    } else if (cleared_row >= 2) {
        if (last_move == T_SPIN_MINI || last_move == T_SPIN) {
            frame_char[8][2] = "T ";
            frame_char[8][3] = "Sp";
            frame_char[8][4] = "in";
            frame_char[8][5] = "! ";
        }
    }

    pause = false;
}

bool Tetris::isGameOver() {
    return field.isGameOver();
}

void Tetris::gameOverMenu() {
    // Display save/restart menu

    std::cout <<
    "  ▄████  ▄▄▄       ███▄ ▄███▓▓█████     ▒█████   ██▒   █▓▓█████  ██▀███\n"
    " ██▒ ▀█▒▒████▄    ▓██▒▀█▀ ██▒▓█   ▀    ▒██▒  ██▒▓██░   █▒▓█   ▀ ▓██ ▒ ██▒\n"
    "▒██░▄▄▄░▒██  ▀█▄  ▓██    ▓██░▒███      ▒██░  ██▒ ▓██  █▒░▒███   ▓██ ░▄█ ▒\n"
    "░▓█  ██▓░██▄▄▄▄██ ▒██    ▒██ ▒▓█  ▄    ▒██   ██░  ▒██ █░░▒▓█  ▄ ▒██▀▀█▄\n"
    "░▒▓███▀▒ ▓█   ▓██▒▒██▒   ░██▒░▒████▒   ░ ████▓▒░   ▒▀█░  ░▒████▒░██▓ ▒██▒\n"
    " ░▒   ▒  ▒▒   ▓▒█░░ ▒░   ░  ░░░ ▒░ ░   ░ ▒░▒░▒░    ░ ▐░  ░░ ▒░ ░░ ▒▓ ░▒▓░\n"
    "  ░   ░   ▒   ▒▒ ░░  ░      ░ ░ ░  ░     ░ ▒ ▒░    ░ ░░   ░ ░  ░  ░▒ ░ ▒░\n"
    "░ ░   ░   ░   ▒   ░      ░      ░      ░ ░ ░ ▒       ░░     ░     ░░   ░\n"
    "      ░       ░  ░       ░      ░  ░       ░ ░        ░     ░  ░   ░\n"
    "                                                     ░\n"
    << std::endl;

    // Clear input buffer
    std::cout << "Press Enter to continue..." << std::flush;
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');

    std::cout << "Do you want to save our score? (y/n) " << std::flush;
    std::string save_score;
    std::cin >> save_score;
    // Check if input does not exist
    if (save_score.empty()) std::cin >> save_score;

    while (!(save_score == "y" || save_score == "Y" ||
            save_score == "n" || save_score == "N")) {
        std::cout << "Type again." << std::endl;
        std::cout << "Do you want to save our score? (y/n) " << std::flush;
        std::cin >> save_score;
    }

    if (save_score == "y" || save_score == "Y") {
        score.writeFile();
        std::cout << "Saved." << std::endl;
    }

    std::cout << "Do you want to restart? (y/n) " << std::flush;
    std::string restart_ans;
    std::cin >> restart_ans;
    while (!(restart_ans == "y" || restart_ans == "Y" ||
             restart_ans == "n" || restart_ans == "N")) {
        std::cout << "Type again." << std::endl;
        std::cout << "Do you want to restart? (y/n) " << std::flush;
        std::cin >> restart_ans;
    }

    if (restart_ans == "y" || restart_ans == "Y") {
        restart();
    }
}

void Tetris::restart() {

    field.reset();
    score.reset();
    set.shuffle();

    combo = 0;
    b2b = 0;
    last_move = INVALID;
    last_key = NONE;
    speed_multiplier = 1.0;

    delete mino_next;
    delete mino_hold;
    delete mino_shadow;

    mino_next = nullptr;
    mino_hold = nullptr;
    mino_shadow = nullptr;

    startRound();
}
