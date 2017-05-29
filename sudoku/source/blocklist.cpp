#include "blocklist.h"
#include "sudoku.h"

BlockList::BlockList(unsigned digit,
					 unsigned y, unsigned x,
					 const Coordinate & size) : 
                                            std::list<Coordinate>(),
                                            digit(digit) {
    const unsigned X_    = size.x;
    const unsigned Y_    = size.y;
    const unsigned SIZE_ = X_ * Y_;
    for ( unsigned i = 0; i < SIZE_; i++) {
        // Blocking on horizontal
        if (i != y) {
            this->push_back(Coordinate(i, x));
        }
        
        // Blocking on vertical
        if (i != x) {
            this->push_back(Coordinate(y, i));
        }
    }
    
    // Counting square coordinates
    const int squareStartX = x - x % X_;
    const int squareStartY = y - y % Y_;
  
    // Blocking in square
    for ( unsigned i = squareStartY, squareFinishY = squareStartY + Y_; i < squareFinishY; i++)   
        for ( unsigned j = squareStartX, squareFinishX = squareStartX + X_; j < squareFinishX; j++)
            if ( (i != y) && (j != x))
                this->push_back(Coordinate(i, j));

}
