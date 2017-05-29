/*  
 * operation.h
 *
 * FreeCell operation class header
 *
 * For FreeCell Solver
 *
 * Copyright (C) Pavel Kryukov, 2011
*/

#ifndef OPERATION_H
#define OPERATION_H

#include <iostream>
#include <vector>

class Operation {
    // Source and destination
    unsigned from;
    unsigned to;
public:
    // Constructors
    Operation() {}
    Operation(unsigned from, unsigned to) : from(from), to(to) {}

    inline unsigned getFrom() const {
        return from;
    }

    inline unsigned getTo() const {
        return to;
    }

    void copy(const Operation & second);

    bool operator!= (const Operation & secondObj) {
            return (this->from == secondObj.to) && (this->to == secondObj.from);
        }

    // Dump
    friend std::ostream & operator<< ( std::ostream & out, const Operation & item);
};

#endif