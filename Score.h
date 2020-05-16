//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#ifndef ASSN3_SCORE_H
#define ASSN3_SCORE_H



class Score {
private:
    int score;

public:
    int getScore() const;
    void add(int s);
    void reset();
    void writeFile();

public:
    Score();
};


#endif //ASSN3_SCORE_H
