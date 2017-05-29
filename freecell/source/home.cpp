/*  
 * home.cpp
 *
 * Solitaire home zone class implementation.
 *
 * For FreeCell Solver
 *
 * Copyright (C) Pavel Kryukov, 2011
*/

#include "home.h"
#include "card.h"

// Init with zero cards
Home::Home() : totalCards(52) {
    for (unsigned i = 0; i < 4; i++) {
       cards[i] = new Card(i);
    }
}

// Add and remove
void Home::addCard(const Card & card) {
    ++(*cards[card.suit]);
    --totalCards;
}
    
void Home::removeCard(const Card & card) {
    --(*cards[card.suit]);
    ++totalCards;
}

// Checks if card can be put to top
unsigned Home::isFor(const Card & card) const {
    return (*cards[card.suit] < card) ? card.suit : 4;
}

// Returns top card of selected suit
Card Home::getTop(unsigned suit) const {
     return Card(suit, cards[suit]->value);
}

// Returns true, if all card with opposite color and greater value is in home
// Or card is two or ace.
bool Home::isGoodFor(const Card & card) const {
    return ( (card < *cards[!(card.suit % 2)]) && 
             (card < *cards[2 + !(card.suit % 2)]) )
           || (card.value <= 2);
}

// Returns true, if card is greater on 4 degrees than cards of opposite color in home
bool Home::isBadFor(const Card & card) const {
return   (card.value - cards[!(card.suit % 2)]->value > 4 ) && 
         (card.value - cards[2 + !(card.suit % 2)]->value > 4 );
}

// Dump
std::ostream& operator<< (std::ostream & out, const Home & item) {
     return out << item.cards[0]->value << ' ' << item.cards[1]->value << ' ' 
                << item.cards[2]->value << ' ' << item.cards[3]->value << ' ';
}

// Hash
std::string Home::hash() const {
    std::string result;
    for (unsigned i = 0; i < 4; i++) {
        result+= ('0' + cards[i]->value);
    }
    return result;
}
