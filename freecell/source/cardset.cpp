/*
 * cardset.cpp 
 *
 * Card set class implementation
 *
 * For FreeCell Solver
 *
 * Copyright (C) Pavel Kryukov, 2011
*/

#include "cardset.h"

// Constructor of full 54-card 
CardSet::CardSet() : std::set<char>() {
    for ( unsigned i = 0; i < 52; ++i) {
         this->insert('0' + i);
    }
}