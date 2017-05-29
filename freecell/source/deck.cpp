/*
 * deck.cpp
 *
 * FreeCell game deck class implementation
 *
 * For FreeCell Solver
 *
 * Copyright (C) Pavel Kryukov, 2011
*/

#include <puzzle/reorderer.h>

#include "deck.h"
#include "cardset.h"

bool Deck::isAutoComplete() const {
    for (unsigned i = 0; i < ColumnCount; i++) {
        if (!stacks[i].isOrdered())
            return false;
    }
    return true;
}

// Returns number of first free cell.
// If there's no, returns number of last.
unsigned Deck::freeCellNum() const {
    for (unsigned j = 0; j < FreeCellCount; j++) {
        if (freeCells[j] == 0)
            return j;
    }
    return FreeCellCount;
}

// Makes operation on source and destination
void Deck::makeOperation(unsigned from, unsigned to) {
    // Temporary card.
    Card* card;

    // From stacks
    if (from < ColumnCount) {
        card = new Card(stacks[from].top());
        stacks[from].pop();
    }

    // From freecells
    else if (from < ColumnCount + FreeCellCount) {
        card = new Card(*freeCells[from % ColumnCount]);

        // Deleting card and zeroing pointer
        delete freeCells[from % ColumnCount];
        freeCells[from % ColumnCount] = 0;
    }

    // From home
    else {
        card = new Card(home.getTop(from % (ColumnCount + FreeCellCount)));
        home.removeCard(*card);
    }

    // To stacks
    if (to < ColumnCount) {
        stacks[to].push(*card);
    }

    // To freecells
    else if (to < ColumnCount + FreeCellCount) {
        freeCells[to % ColumnCount] = new Card(*card);
    }

    // To home
    else {
        home.addCard(*card);
    }
    
    delete card;
}

std::string Deck::destToString(unsigned what) {
    std::string result;
    if (what < ColumnCount) {
        result = "COLUMN ";
        result += (what + '0');
        return result;
    }
    if ((what >= ColumnCount) && (what < (ColumnCount + FreeCellCount))) {
        result = "FREECELL ";
        result += ((what % ColumnCount) + '0');
        return result;
    }
    return "HOME";
}

// Main eurystic method
// Returns ordered vector of operations
// First operation is the best, last is the worst
void Deck::getListOfOperations(std::vector<Operation> & vector) const {
    // Reorder list
    OperationOrderList<Operation, unsigned> list; 

    // Go through stacks
    for (unsigned i = 0; i < ColumnCount; i++) {
        // From free cell to empty stack
        if (!stacks[i].size()) {
            for (unsigned j = 0; j < FreeCellCount; j++) {
                // Check correctness
                if (freeCells[j] != 0) {

                    // More free cells is always good!
                    list.push_back(Operation(ColumnCount + j, i), (1 << 20) * freeCells[j]->getValue());
                }
            }
            
            // If stack is empty, skip it
            continue;
        }   

        // Getting top card
        Card topCard = stacks[i].top();
        
        // Getting disorder of current stack
        const unsigned disorder = stacks[i].disorder();

        // Checking ability of move from stack to home
    
        const unsigned homeAddr = home.isFor(topCard);
        if (homeAddr < 4) {
            
            if (home.isGoodFor(topCard)) {
                // If there're few cards, drop it to home and forget
                list.clear();
                list.push_back(Operation(i, ColumnCount + FreeCellCount + homeAddr), (1 << 30));
                break;

            }

            else if (!home.isBadFor(topCard)) {
                // Otherwise, can be pushed with hight probability
                list.push_back(Operation(i, ColumnCount + FreeCellCount + homeAddr), (1 << 20));
            }
        }

        // ..from stack to free cells
        unsigned freeCellNum = this->freeCellNum();
        if ((freeCellNum != FreeCellCount) && (stacks[i].size() != 1)) {
                list.push_back(Operation(i, ColumnCount + freeCellNum), topCard.getValue() * disorder);
        }

        // ..from stacks to stacks
        for (unsigned j = 0; j < ColumnCount; j++) {

            // If same stack, skip
            if ( i == j ) continue;
                

            if ( stacks[j].size() > 0) {

                const Card & topCardThis = stacks[j].top();

                // From stack to non-empty stack
                // Checking correctness (value and color)
                if ((topCard < topCardThis) && !(topCard || topCardThis)) {

                    // We do not move cards to kings (exc. when stack is little)
                    if (!((topCardThis.getValue() > 12) && (stacks[j].size() > 2))) {

                        // If card is low and source stack is disordered, push it with higher priority
                        list.push_back(Operation(i, j), (15 - topCard.getValue()) * disorder);
                    }
                    else {
                        
                        // If card is low and source stack is disordered, push it with higher priority
                        list.push_back(Operation(i, j), 0);
                    }

                }
            }
            else {            
                 // From stack to empty stack
                 // Do not move cards from empty stacks to empty stacks.
                 if (stacks[i].size() > 1) {
                     // Otherwise, we prefer not to use empty stack 
                     list.push_back(Operation(i, j), topCard.getValue() * disorder);
                 }
            }
       }

        // From free cell to stack
            for (unsigned j = 0; j < FreeCellCount; j++) {
                // Check correctness
                if ((freeCells[j] != 0) && (*freeCells[j] < topCard) && !(topCard || *freeCells[j])) {

                    // More free cells is always good!
                    list.push_back(Operation(ColumnCount + j, i), 1 << 25);
                }
            }
    }
      
    // From free cell to home
    for (unsigned j = 0; j < FreeCellCount; j++) {

        if (freeCells[j] != 0) {
            const unsigned homeAddr = home.isFor(*freeCells[j]); 
            if (homeAddr < 4) {
                if (home.isGoodFor(*freeCells[j])) {
                    // If there're few cards, drop it to home and forget
                    list.clear();
                    list.push_back(Operation(ColumnCount + j, ColumnCount + FreeCellCount + homeAddr), (1 << 30)); 
                    break;
                }
                if (home.isBadFor(*freeCells[j])) {
                    // If card is more useful on deck, use it on deck.             
                    list.push_back(Operation(ColumnCount + j, ColumnCount + FreeCellCount + homeAddr), 1 << 25);
                }

            }
        }
    }
    
    list.getVector(vector);

}

Deck::Deck(const Deck & source) : stacks(source.stacks), home(),  isCorrect_(source.isCorrect_) {
    for ( unsigned i = 0; i < FreeCellCount; i++) {
        freeCells[i] = 0;
    }
}

// Constructor from file
Deck::Deck(std::istream & source) : stacks(ColumnCount), home() {
    // Set of cards. Used for checking
    CardSet cardSet;

    isCorrect_ = true;

    // Init freecells
    for ( unsigned i = 0; i < FreeCellCount; i++) {
        freeCells[i] = 0;
    }

    // Reading lines..
    for ( unsigned i = 0; i < ColumnCount; i++) {
        // First stacks are 6-cards, next are 7-cards
        for (unsigned j = 0; j < (6 + (i / 4)); j++) {
            
            // Reading
            std::string buffer;
            source >> buffer;
            Card card(buffer);

            // If card is not in set (used twice), input is incorrect
            // Else, remove it from set.
            if (cardSet.find(card.hash()) == cardSet.end()) {
                isCorrect_ = false;
            }
            else {
                cardSet.erase(card.hash());
            }
            
            // Pushing
            stacks[i].push(card);
        }
    }

    // If some cards were not initialized..
    if (cardSet.size() != 0) {
        isCorrect_ = false;
    }
}

// Dump
std::ostream & operator<< (std::ostream & out, const Deck & item) {
    // Dump of stacks
    for ( unsigned i = 0; i < Deck::ColumnCount; i++) {
        out << item.stacks[i] << std::endl;
    }

    // Dump of home
    out << item.home << std::endl;
    return out;
}

// Hash
std::string Deck::hash() const {
    std::string string;
    for ( unsigned i = 0; i < ColumnCount; i++) {
        string.append(stacks[i].hash());
    }
    string.append(home.hash());
    return string;
}