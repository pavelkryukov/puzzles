#include <iostream>
#include <ctime>
#include <cstdlib>

#include "operation.h"
#include "fifteen.h"

#include <puzzle/puzzle.h>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "Syntax error" << std::endl;
        return -1;
    }
    std::ifstream input;
    input.open(argv[1]);

    Puzzle<Fifteen, Operation> fifteen(input);

    input.close();

    fifteen.solveMinimumDown();


    return 0;
}