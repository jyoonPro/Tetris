cmake_minimum_required(VERSION 3.17)
project(Assn3)

set(CMAKE_CXX_STANDARD 11)

add_executable(Assn3 main.cpp Block.cpp Block.h ConsoleEngine.cpp ConsoleEngine.h constant.h enum.h Tetris.cpp Tetris.h Tetrimino.cpp Tetrimino.h Tetriminos/Mino_I.cpp Tetriminos/Mino_I.h Tetriminos/Data.cpp Tetriminos/Mino_O.cpp Tetriminos/Mino_O.h Tetriminos/Mino_T.cpp Tetriminos/Mino_T.h Tetriminos/Mino_L.cpp Tetriminos/Mino_L.h Tetriminos/Mino_J.cpp Tetriminos/Mino_J.h Tetriminos/Mino_S.cpp Tetriminos/Mino_S.h Tetriminos/Mino_Z.cpp Tetriminos/Mino_Z.h Tetriminos/_all.h Playfield.cpp Playfield.h MinoSet.cpp MinoSet.h Score.cpp Score.h)