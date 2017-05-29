/*
 * cell.cpp
 *
 * Sudoku field cell implementation (code)
 *
 * Pavel Kryukov (C) 2011
*/

#include <iostream>

#include "cell.h"

Cell::Cell(const Cell & source)
{
        this->digit_ = source.digit_;
        this->max_ = source.max_;
        this->blockSet_ = new char[max_ + 1];
        for ( unsigned i = 0; i < (max_ + 1); ++i)
            this->blockSet_[i] = 0;
}

Cell::Cell(const unsigned max)
    : digit_(0)
    , max_(max)
{
    this->blockSet_ = new char[max_ + 1];
    for ( unsigned i = 0; i < (max_ + 1); ++i)
        this->blockSet_[i] = 0;
}

std::ostream & operator<< (std::ostream & out, const Cell & item)
{
    return out <<
        (item.digit_ 
            ? (char)( ( (item.digit_ <= 9) ? '0' : 'A' - 10) + item.digit_) 
            : ' ');
}

const unsigned Cell::nonBlocked() const
{
    unsigned digit = 0;
    for ( unsigned i = 1; i <= max_; i++)
        if (!(blockSet_[i])) {
            if (digit)
                // If there was another digit, return 0
                return 0;
            else
                digit = i;
	}

    return digit;
}

const unsigned Cell::nonBlockedCount() const
{
    unsigned count = 0;
    for ( unsigned i = 1; i <= max_; i++)
        if (!(blockSet_[i]))
            count++;

    return count;
}
