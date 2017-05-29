#include <fstream>
#include <string>
#include <iostream>

#include "sudoku.h"
#include "blocklist.h"

// Blocking and unblocking on list 
void Sudoku::Block(const BlockList & blocklist)
{
    BlockList::const_iterator it;
    for ( it = blocklist.begin(); it != blocklist.end(); ++it)
        Table_[it->y][it->x].block(blocklist.digit);
}

void Sudoku::Unblock(const BlockList & blocklist) 
{
    BlockList::const_iterator it;
    for ( it = blocklist.begin(); it != blocklist.end(); ++it)
        Table_[it->y][it->x].unblock(blocklist.digit);
}

/**
 * Zero constructor
*/
Sudoku::Sudoku(const unsigned Y, const unsigned X) 
    : Y(Y)
    , X(X)
    , SIZE(X * Y)
    , size(Coordinate(Y, X))
{
    Table_.resize(SIZE, std::vector<Cell>(SIZE, Cell(SIZE)));
    status_ = NOTSOLVED;
}

/**
 * Constructor from file
*/
Sudoku::Sudoku(const unsigned Y, const unsigned X, std::ifstream &fp)
    : Y(Y)
    , X(X)
    , SIZE(X * Y)
    , size(Coordinate(Y, X))
{
    Table_.resize(SIZE, std::vector<Cell>(SIZE, Cell(SIZE)));

    std::string buffer;
    for ( unsigned i = 0; i < SIZE; i++)
    {
        std::getline(fp, buffer);
        for ( unsigned j = 0; j < SIZE; j++)
        {
            if ((buffer[j] >= '1') && (buffer[j] <= '9'))
                Table_[i][j] = (buffer[j] - '1') + 1;

            if ((buffer[j] >= 'A') && (buffer[j] <= 'Z'))
                Table_[i][j] = (buffer[j] - 'A') + 10;

        }
    }
    status_ = NOTSOLVED;
}

/**
 * Blocking digit process based on data from predefined cells
*/
void Sudoku::strongBlocking()
{
    for ( unsigned i = 0; i < SIZE; i++)
        for ( unsigned j = 0; j < SIZE; j++)
            if ( Table_[i][j].getunsigned())
                // Blocking list is not necessary so it's removed
                this->Block(BlockList(Table_[i][j].getunsigned(), i, j, this->size));
}

/*
 * Checks if any digit appears twice on same row, column or square.
 * If it is, it should be "self-blocked"
*/
const bool Sudoku::checkCorrect() const
{
    for ( unsigned i = 0; i < SIZE; i++)
        for ( unsigned j = 0; j < SIZE; j++)
            if ( Table_[i][j].getunsigned() && Table_[i][j].isSelfBlocked())
                return false;
    return true;
}

/**
 * Filling cells based on information about probable values
 *
 * If there exists only one non-blocked digit, it's set to cell and blocks necessary cells
*/
void Sudoku::subFill()
{
    // Flag shows if there were any changes
    bool flag;
    do 
    {
        flag = false;
        for ( unsigned i = 0; i < SIZE; i++)
            for ( unsigned j = 0; j < SIZE; j++)
                if ( !Table_[i][j].getunsigned())
                {
                    // Finding non-blocked digit
                    unsigned sugg = Table_[i][j].nonBlocked();

                    // If there's one, it's set as STRONG and blocks necessary cells
                    if (sugg)
                    {
                        Table_[i][j] = sugg;

                        this->Block(BlockList(sugg, i, j, this->size));
    
                        // Any change — flag is true
                        flag = true;
                    }
                }
    } while (flag);
}

void Sudoku::fillTasks() const
{
   for ( unsigned i = 0; i < SIZE; i++)
        for ( unsigned j = 0; j < SIZE; j++)
            // If cell is not filled, it should be added to tasks list
            if ( !Table_[i][j].getunsigned())
                stack_.push_back( Task( i, j, Table_[i][j].nonBlockedCount(), this->size, 1));
}



bool Sudoku::iterationer()
{
    TaskList::iterator it = stack_.begin();
    while (it != stack_.end())
        // If there's no suggestions 
        if (it->digit > SIZE) {
            // If we returned to the first cell, it means that sudoku is unsolvable
            if (it == stack_.begin()) return false;
    
            // Cleaning current suggestion
            it->digit = 1;

            // Removing previous suggestion and setting its new value as ++ of previous

            // goto previous
            --it;
         
            this->Unblock(*it);

            // to next suggestions (e.g. 5 caused lock, then try 6)
            it->digit++;
        }
        else {
            // If suggestion is blocked on this cell, try next (5 is blocked, try 6)
            if ( Table_[it->y][it->x].isBlocked(it->digit)) {
                it->digit++;
            }
            else {
            // If not, block digit in necessary cells and go to next task 
                Block(*it);
                ++it;
            }
        }
    return true;
}

void Sudoku::fillSugg()
{
    TaskList::const_iterator it;
    for ( it  = stack_.begin(); it != stack_.end(); ++it)
        Table_[it->y][it->x] = it->digit;
}
 
/**
 * Printing method
*/
std::ostream & operator<< (std::ostream & out, const Sudoku & item)
{
    for ( unsigned i = 0; i < item.SIZE; i++) {
        // Adding break line
        if ( !(i % item.Y)) 
            out << std::endl;
        for ( unsigned j = 0; j < item.SIZE; j++) {
            // Adding break column
            if ( !(j % item.X)) 
                out << ' ';
            out << item.Table_[i][j];
        }
        out << std::endl;
    }
    return out;
}

/**
 * Solve it, baby
 *
 * If returns false, sudoku is unsolvable
*/
void Sudoku::solve()
{
    strongBlocking();
    if (!checkCorrect()) {
        status_ = INCORRECT;
    }
    else {
        subFill();        // optional

        fillTasks();
        stack_.sort();    // optional

        if (iterationer()) {
            fillSugg();
            status_ = SOLVED;
        }
        else {
            status_ = UNSOLVABLE;
        }
    }
}