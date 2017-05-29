/*
 * cardset.h 
 *
 * Card set class header
 *
 * For FreeCell Solver
 *
 * Copyright (C) Pavel Kryukov, 2011
*/

#ifndef CARDSET_H
#define CARDSET_H

#include <set>

// Card is coded with char.
// Every card in set is unique.
class CardSet : public std::set<char> {
public:
    // Constructor creates full 52-card set 
    CardSet();
};

#endif