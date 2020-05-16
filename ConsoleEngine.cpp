//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#include <cstdlib>
#include <windows.h>
#include "ConsoleEngine.h"
#include "constant.h"

// Constructor
ConsoleEngine::ConsoleEngine() {
    // Populate the base frame
    frame_char = new std::string*[GAME_HEIGHT];
    frame_color = new Color*[GAME_HEIGHT];
    for (int i = 0; i < GAME_HEIGHT; i++) {
        frame_char[i] = new std::string[GAME_WIDTH];
        frame_color[i] = new Color[GAME_WIDTH]();
    }

    // Initialize string array
    for (int i = 0; i < GAME_HEIGHT; i++) {
        for (int j = 0; j < GAME_WIDTH; j++) {
            frame_char[i][j] = BLANK_STR;
        }
    }

    // Generate game walls
    // Line 0 -> 9
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j < GAME_WIDTH; j++) {
            frame_char[i][j] = WALL_ICON;
            frame_color[i][j] = WHITE;
        }
    }
    // Line 10 -> GAME_HEIGHT
    for (int i = 10; i < GAME_HEIGHT; i++) {
        for (int j = 7; j <= FIELD_WIDTH + 8; j++) {
            frame_char[i][j] = WALL_ICON;
            frame_color[i][j] = WHITE;
        }
    }
    // Clear field for Hold, Next
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 6; j++) {
            frame_char[i][j] = BLANK_STR;
        }
        for (int j = 9 + FIELD_WIDTH; j < GAME_WIDTH - 1; j++) {
            frame_char[i][j] = BLANK_STR;
        }
    }
    // Score / Combo Labels
    frame_char[7][1] = "Co";
    frame_char[7][2] = "mb";
    frame_char[7][3] = "o ";
    frame_char[7][FIELD_WIDTH + 9] = "Sc";
    frame_char[7][FIELD_WIDTH + 10] = "or";
    frame_char[7][FIELD_WIDTH + 11] = "e ";
    for (int j = 4; j <= 6; j++) {
        frame_char[7][j] = BLANK_STR;
    }
    for (int j = FIELD_WIDTH + 12; j < GAME_WIDTH - 1; j++) {
        frame_char[7][j] = BLANK_STR;
    }
    for (int j = 1; j <= 6; j++) {
        frame_char[8][j] = BLANK_STR;
    }
    for (int j = 9 + FIELD_WIDTH; j < GAME_WIDTH - 1; j++) {
        frame_char[8][j] = BLANK_STR;
    }

    curr_key = NONE;
    is_running = false;
    pause = false;
}

// Destructor
ConsoleEngine::~ConsoleEngine() {
    // Delete frame
    for (int i = 0; i < GAME_HEIGHT; i++) {
        delete[] frame_char[i];
        delete[] frame_color[i];
    }
    delete[] frame_char;
    delete[] frame_color;
}

void ConsoleEngine::asyncRender() {
    // Clear screen and disable cin echo
    printf("\033[2J");
    printf("\e[?25l");
    system("stty -echo");

    std::string color_code;

    while (is_running) {
        if (!pause) {
            gotoxy(0, 0);

            for (int i = 0; i < GAME_HEIGHT; i++) {
                for (int j = 0; j < GAME_WIDTH; j++) {
                    switch (frame_color[i][j]) {
                        case RED:     color_code = cRED;     break;
                        case GREEN:   color_code = cGREEN;   break;
                        case YELLOW:  color_code = cYELLOW;  break;
                        case BLUE:    color_code = cBLUE;    break;
                        case MAGENTA: color_code = cMAGENTA; break;
                        case CYAN:    color_code = cCYAN;    break;
                        default:      color_code = cWHITE;
                    }
                    std::cout << color_code << frame_char[i][j] << cRESET;
                }
                std::cout << "\n";
            }
            std::cout << std::flush; // Flush just in case
            std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_INT));
        }
    }
}

void ConsoleEngine::getKey() {
    // Keystroke priority from top to bottom
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) curr_key = SPACE;
    else if (GetAsyncKeyState(0x43) & 0x8000) curr_key = keyC;
    else if (GetAsyncKeyState(0x53) & 0x8000) curr_key = keyS;
    else if (GetAsyncKeyState(0x57) & 0x8000) curr_key = keyW;
    else if (GetAsyncKeyState(0x58) & 0x8000) curr_key = keyX;
    else if (GetAsyncKeyState(0x41) & 0x8000) curr_key = keyA;
    else if (GetAsyncKeyState(0x44) & 0x8000) curr_key = keyD;
    else if (GetAsyncKeyState(0x4D) & 0x8000) curr_key = keyM;
    else curr_key = NONE;
}

void ConsoleEngine::start() {
    is_running = true;
    pause = false;

    render_thread = std::thread(&ConsoleEngine::asyncRender, this);
    render_thread.detach();
}

void ConsoleEngine::stop() {
    pause = true;
    is_running = false;
    system("clear");
    system("stty echo");
    printf("\e[?25h");
    // Threads are automatically terminated
}
