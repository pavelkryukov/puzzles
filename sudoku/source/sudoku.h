/*
 * sudoku.h
 *
 * Sudoku solver implementation (template header)
 *
 * Pavel Kryukov (C) 2011
*/

#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <fstream>

#include "cell.h"
#include "blocklist.h"
#include "task.h"

/**
 *    Sudoku template
 *    S — size of one middle square
*/
class Sudoku {
public:
    enum SudokuStatus {
        NOTSOLVED,
        SOLVED,
        UNSOLVABLE,
        INCORRECT
    };
private:
    const unsigned Y;
    const unsigned X;

    // Size — size of big square
    const unsigned SIZE;

    const Coordinate size;

    // Container of cells
    std::vector< std::vector< Cell > > Table_;

    // Blocking based on STRONG cells
    void strongBlocking();

    // Checking if correct
    const bool checkCorrect() const;

    // Filling cells based on information about probable values
    void subFill();

    // List of tasks
    typedef std::list<Task> TaskList;
    mutable TaskList stack_;

    // Fill list of tasks
    void fillTasks() const;

    // Make suggestions
    bool iterationer();

    // Fill suggestions to table
    void fillSugg();

    // Status of puzzle
    SudokuStatus status_;

    // Block/Unblock of blocklist
    void   Block(const BlockList & blocklist);
    void Unblock(const BlockList & blocklist);

public:
    // Zero constructor
    Sudoku(const unsigned Y, const unsigned X);

    // File constructor
    Sudoku(const unsigned Y, const unsigned X, std::ifstream &);

    // Solving method
    void solve();

    // Returning status
    inline const SudokuStatus getStatus() const {
        return this->status_;
    }

    // Dumping method
    friend std::ostream & operator<< (std::ostream & out, const Sudoku & item);
};

#endif //SUDOKU_H
