/*
 * main.cpp
 *
 * Sudoku solver main program
 *
 * Kryukov Pavel (C) 2011
*/

#include <ctime>

#include <iostream>

#include "sudoku.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Syntax error" << std::endl;
        return -1;
    }

    std::ifstream inputfile;
    inputfile.open(argv[1]);
    Sudoku sudoku(3,3,inputfile);
    inputfile.close();

    std::cout << sudoku;

    clock_t t0 = std::clock();
    sudoku.solve();
    std::cout << "Time: " << (float)(std::clock() - t0) / CLOCKS_PER_SEC << " s" << std::endl;

    switch (sudoku.getStatus()) {
        case Sudoku::INCORRECT:
            std::cout << "Incorrect" << std::endl;
            break;
        case Sudoku::UNSOLVABLE:
            std::cout << "Unsolvable" << std::endl;
            break;
        case Sudoku::SOLVED:
            std::cout << sudoku;
            break;
        default:
            std::cout << "Unrecognized error" << std::endl;
    }

 //   delete sudoku;
    return 0;
}
