/*
 * deck.h 
 *
 * FreeCell game deck class header
 *
 * For FreeCell Solver
 *
 * Copyright (C) Pavel Kryukov, 2011
*/

#ifndef DECK_H
#define DECK_H

#include <string>
#include <iostream>
#include <vector>

#include "card.h"
#include "cardstack.h"
#include "operation.h"
#include "home.h"

class Deck {
private: 
    // Sizes
    static const unsigned ColumnCount = 8;
    static const unsigned FreeCellCount = 4;

    // Stacks of cards
    std::vector<CardStack> stacks;

    // Free cells
    Card* freeCells[FreeCellCount];
    unsigned freeCellNum() const;
    
    // Home zone
    Home home;

    // Making operation method
    void makeOperation(unsigned from, unsigned to);
       
    // Flag of build correctness
    bool isCorrect_;

    bool isAutoComplete() const;
public:
    // Constructor from input
    Deck(std::istream & source);
    Deck(const Deck & source);

    // Getter of correctness
    inline bool isCorrect() {
        return isCorrect_;
    }

    // Gives ordered vector of operations on deck
    void getListOfOperations(std::vector<Operation> & vector) const;

    // Making operations
    inline void   makeOperation(const Operation & operation) {
        makeOperation(operation.getFrom(), operation.getTo());
    }
    inline void unmakeOperation(const Operation & operation) {
        makeOperation(operation.getTo(), operation.getFrom());
    }

    // Destination to string converter
    static std::string destToString(unsigned what);

    // Checking if finished
    inline bool isFinished() const {
        return this->isAutoComplete() || (home.getTotalCards() <= ColumnCount + FreeCellCount);
    }

    // Dump
    friend std::ostream & operator<< (std::ostream & out, const Deck & item);

    // Returns hash
    std::string hash() const;

    inline unsigned getTotalCards() const {
        return home.getTotalCards();
    }

};

#endif