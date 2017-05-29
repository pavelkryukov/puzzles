/*
 * cardstack.h 
 *
 * Card stack class header
 *
 * For FreeCell Solver
 *
 * Copyright (C) Pavel Kryukov, 2011
*/

#ifndef CARDSTACK_H
#define CARDSTACK_H

#include <stack>
#include <string>
#include <list>

#include "card.h"

class CardStack : public std::stack<Card, std::list<Card> > {
public:
    // Zero constructor
    CardStack() : std::stack<Card, std::list<Card> > () {}

    // Top of the source stack
    CardStack(CardStack & stack, unsigned count);

    // Value of stack disorder
    unsigned disorder() const;

    bool isOrdered() const;

    // Dump
    friend std::ostream & operator<< (std::ostream & out, const CardStack & item);

    // Hash string of stack
    const std::string hash() const;
};

#endif