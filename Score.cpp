//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#include <fstream>
#include <iostream>
#include "Score.h"
#include "constant.h"

// Constructor / Destructor
Score::Score() {
    score = 0;
}

// Function Definitions
int Score::getScore() const { return score; }

void Score::add(int s) { score += s; }
void Score::reset() { score = 0; }


void Score::writeFile() {
    std::ofstream temp;
    temp.open(".tmp");

    if (temp.is_open()) {
        temp << score << std::endl;

        std::ifstream scoresheet;
        scoresheet.open(SCORESHEET);

        if (scoresheet.is_open()) {
            temp << scoresheet.rdbuf(); // Copy over original content
            scoresheet.close();
        }

        temp.close();
    } else {
        std::cout << "Error: Could not open file." << std::endl;
        return;
    }

    std::remove(SCORESHEET);
    std::rename(".tmp", SCORESHEET);
}