/*  
 * operation.cpp
 *
 * FreeCell operation class implementation
 *
 * For FreeCell Solver
 *
 * Copyright (C) Pavel Kryukov, 2011
*/

#include "operation.h"
#include "deck.h"

// Dump
std::ostream & operator<< ( std::ostream & out, const Operation & item) {
    return out << Deck::destToString(item.from) << " => " << Deck::destToString(item.to);
}

void Operation::copy(const Operation & second) {
    this->to = second.to;
    this->from = second.from;
}