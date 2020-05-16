//
// Honor Code
// I completed this programming task without the improper help of others.
// Copyright (c) 2020 Joseph Yoon. All rights reserved.
//
#ifndef ASSN3_CONSOLEENGINE_H
#define ASSN3_CONSOLEENGINE_H

#include <iostream>
#include <thread>
#include "enum.h"

class ConsoleEngine {
private:
    std::thread render_thread;

protected:
    bool is_running;
    bool pause;
    std::string **frame_char;
    Color **frame_color;
    Keystroke curr_key;

    void asyncRender();

public:
    void getKey();
    void start();
    void stop();

    ConsoleEngine();
    ~ConsoleEngine();
};


#endif //ASSN3_CONSOLEENGINE_H
