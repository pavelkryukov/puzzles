/*
 * cell.h 
 *
 * Sudoku field cell implementation (header)
 *
 * Pavel Kryukov (C) 2011
*/

#ifndef CELL_H
#define CELL_H

#include <vector>

class Cell {
private:
    // unsigned inside
    unsigned digit_;

    // Max digit
    unsigned max_;

    // Set of blocked digits
    char* blockSet_;
public:
    // Default constructor
    Cell(unsigned max);

    // Copy constructor
    Cell(const Cell & source);

    inline ~Cell()
    {
        if (max_) delete[] blockSet_;
    }

    // Get cell as char
    friend std::ostream & operator<< (std::ostream & out, const Cell & item);

    // Get cell as integer
    inline const unsigned getunsigned() const { return digit_; }

    // Set digit
    inline void operator=(const unsigned digit) { digit_ = digit; }

    // Add digit to block-list
    inline void block(const unsigned digit) { blockSet_[digit]++; }

    // Remove digit from block-list
    inline void unblock(const unsigned digit) { blockSet_[digit]--; }

    // Check if digit is blocked in this cell
    inline const bool isBlocked(const unsigned digit) const
    {
        return (blockSet_[digit] > 0);
    }

    inline const bool isSelfBlocked() const
    {
        return (blockSet_[digit_] > 0);
    }

    // Find if there's only one non-blocked digit.
    // Returns it, otherwise returns 0
    const unsigned nonBlocked() const;

    // Returns count of non-blocked digits
    const unsigned nonBlockedCount() const;
};

#endif //CELL_H