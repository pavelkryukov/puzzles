/*
 * card.h
 *
 * Card class header
 *
 * For FreeCell Solver
 *
 * Copyright (C) Pavel Kryukov, 2011
*/

#ifndef CARD_H
#define CARD_H

#include <string>

#include "home.h"

class Card {
private:
    // Arrsys of values and suit symbolic names
    static const char Values[14];
    static const char Suits[4];
    
    // Home class is friend
    friend class Home;
    friend std::ostream& operator<< (std::ostream & out, const Home & item);

    // 0 - spades, 1 - hearts, 2 - clubs, 3 - diamonds
    // note that black suits are even, red ones are odd.
    unsigned suit;

    // 0 - zero value, 
    // 1 - ace, 
    // 2-10 - 2-10
    // 11 - jacket
    // 12 - queen
    // 13 - king
    unsigned value; 

    inline void operator++ () {
        ++value;
    }

    inline void operator-- () {
        --value;
    }

public:
    // Constructors
    inline Card() : suit(0), value(0) {}
    inline Card(unsigned suit) : suit(suit), value(0) {}
    inline Card(unsigned suit, unsigned value) : suit(suit), value(value) {}
    inline Card(const Card & source) : suit(source.suit), value(source.value) {}
    
    // Constructor by name, e.g. 5H or AS
    Card(const std::string & name);
    
    // Operator of order. Returns true, if only cards have neighbour values, 
    // e.g. Q < K but not J < K.
    friend bool operator< ( const Card & first, const Card & second);
    
    // Operator of color identity.
    // Returns true, if cards have same color.
    friend bool operator|| ( const Card & first, const Card & second);

    // Getters
    inline unsigned getValue() const {
        return value;
    }

    // Dump
    friend std::ostream & operator<< (std::ostream & out, const Card & item);

    // Hash symbol
    char hash() const;
};

std::ostream & operator<< (std::ostream & out, const Card & item);
   
#endif