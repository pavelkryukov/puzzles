/*  
 * card.cpp
 *
 * Card class implementation
 *
 * For FreeCell Solver
 *
 * Copyright (C) Pavel Kryukov, 2011
*/
#include "card.h"

// Initializer
const char Card::Values[14] = {'E', 'A', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K'};
const char Card::Suits[4] = {'S', 'H', 'C', 'D'};

// Constructor from 2-lettered name
Card::Card(const std::string & name) {
    switch (name[0]) {
        case 'A': value = 1; break;
        case '2': value = 2; break;
        case '3': value = 3; break;
        case '4': value = 4; break;
        case '5': value = 5; break;
        case '6': value = 6; break;
        case '7': value = 7; break;
        case '8': value = 8; break;
        case '9': value = 9; break;
        case '0': value = 10; break;
        case 'J': value = 11; break;
        case 'Q': value = 12; break;
        case 'K': value = 13; break;
        default:  value = 0; break;
    }
    switch (name[1]) {
        case 'S': suit = 0; break;
        case 'H': suit = 1; break;
        case 'C': suit = 2; break;
        case 'D': suit = 3; break;
        default:  suit = 0; break;
    }
}

// Operator of order
bool operator< ( const Card & first, const Card & second) {
    return (second.value - first.value) == 1;
}

// Operator of color identity
bool operator|| ( const Card & first, const Card & second) {
    return (first.suit % 2) == (second.suit % 2);
}

// Dump
std::ostream & operator<< (std::ostream & out, const Card & item) {
    return out << Card::Values[item.value] << Card::Suits[item.suit];
}

// Hash symbol
char Card::hash() const {
    return '0' + suit * 13 + value - 1;
}