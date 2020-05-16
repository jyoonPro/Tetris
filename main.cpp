//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#include <iostream>
#include "Tetris.h"

void splash() {
    system("clear");
    std::cout <<
    "████████╗███████╗████████╗██████╗ ██╗███████╗\n"
    "╚══██╔══╝██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝\n"
    "   ██║   █████╗     ██║   ██████╔╝██║███████╗\n"
    "   ██║   ██╔══╝     ██║   ██╔══██╗██║╚════██║\n"
    "   ██║   ███████╗   ██║   ██║  ██║██║███████║\n"
    "   ╚═╝   ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚══════╝\n"
    << std::endl;
}

int main() {
    Tetris tetris;

    // Splash Screen
    splash();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    tetris.startRound();

    return 0;
}
