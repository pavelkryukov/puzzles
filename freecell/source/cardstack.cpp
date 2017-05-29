/*
 * cardstack.cpp
 *
 * Card stack class implementation
 *
 * For FreeCell Solver
 *
 * Copyright (C) Pavel Kryukov, 2011
*/

#include "cardstack.h"

// Cut-constructor
// Cuts <count> top cards from <stack>
CardStack::CardStack(CardStack & stack, unsigned count) : std::stack<Card, std::list<Card> > () {
    for (unsigned i = 0; i < count; i++) {
        this->push(stack.top());
        stack.pop();
    }
}

// Disorder counter
unsigned CardStack::disorder() const  {
    // Counting minimum card and it's position.
    unsigned minimum = 15;
    unsigned pos = 0;
    unsigned curPos = 1;
    for ( container_type::const_iterator it = c.begin(); it != c.end(); ++it, ++curPos) {
        if (it->getValue() < minimum) {
           minimum = it->getValue();
           pos = curPos;
        }
    }
    if (this->top().getValue() == 13)
        return (this->size() + 2) * 15 * this->size();
    // Return
    // Disorder is bigger, if minimum card is near top
    // Also it's bigger, if minimum card is ace or two
    // At final, value is multiplied on size
    return (this->size() - pos + 1) * (15 - minimum) * this->size();          
}

bool CardStack::isOrdered() const {
    if (!this->size()) 
        return true;
    unsigned previous = 15;
    for ( container_type::const_iterator it = c.begin(); it != c.end(); ++it) {
        if (it->getValue() >= previous)
            return false;
        else
            previous = it->getValue();
    }
    return true;
}

// Dump
std::ostream & operator<< (std::ostream & out, const CardStack & item) {
    for ( CardStack::container_type::const_iterator it = item.c.begin(); it != item.c.end(); ++it) {
        out << (*it) << ' ';
    }
    return out;
}

// Hash
const std::string CardStack::hash() const {
    std::string result;
    for ( container_type::const_iterator it = c.begin(); it != c.end(); ++it) {
        result += it->hash();
    }
    result += '%';
    return result;
}