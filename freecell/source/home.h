/*  
 * home.h
 *
 * Solitaire home zone class header.
 *
 * For FreeCell Solver
 *
 * Copyright (C) Pavel Kryukov, 2011
*/

#ifndef HOME_H
#define HOME_H

#include <string>

class Card;

class Home {
    // Cards on top of the home
    Card* cards[4];

    // Total number of cards
    unsigned totalCards;
public:
    Home();

    // Add/Remove
    void addCard(const Card & card);
    void removeCard(const Card & card);

    // Checks is card can be moved to home
    unsigned isFor(const Card & card) const;

    // Returns top of choosed suit
    Card getTop(unsigned suit) const;

    // Eurystic methods
    bool isGoodFor(const Card & card) const;
    bool isBadFor(const Card & card) const;

    // Total cards return
    inline bool isFinished() const {
        return (!totalCards);
    }

    inline unsigned getTotalCards() const {
        return totalCards;
    }

    // Dump
    friend std::ostream& operator<< (std::ostream & out, const Home & item);

    // Hash
    std::string hash() const;
};

#endif