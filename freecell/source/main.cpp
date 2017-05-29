#include <iostream>
#include <fstream>

#include <puzzle/puzzle.h>

#include "operation.h"
#include "deck.h"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "Syntax error" << std::endl;
        return -1;
    }
    std::ifstream input;
    input.open(argv[1]);

    Puzzle<Deck, Operation>  freecell(input);

    input.close();

    freecell.solveMinimumUp();

    return 0;
}