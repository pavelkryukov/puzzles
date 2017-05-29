#include "operation.h"

// Initializers
const char* const Operation::opNames[] = {"UP", "DOWN", "LEFT", "RIGHT", "NOVALID"};
const Operation::EnumType Operation::opNext[] = {DOWN, LEFT, RIGHT, NOVALID, NOVALID};
const Operation::EnumType Operation::opAnti[] = {DOWN, UP, RIGHT, LEFT, NOVALID};
 
void Operation::copy(const Operation & second) {
    this->operation = second.operation;
}

void Operation::operationMake(unsigned & y, unsigned & x) const {
    switch (operation) {
        case UP: 
            --y;
            break;
        case DOWN: 
            ++y;
            break;
        case LEFT: 
            --x;
            break;
        case RIGHT: 
            ++x;
            break;
        default:
            return;
    }
}

void Operation::operationUnMake(unsigned & y, unsigned & x) const {
    switch (operation) {
        case UP: 
            ++y;
            break;
        case DOWN: 
            --y;
            break;
        case LEFT: 
            ++x;
            break;
        case RIGHT: 
            --x;
            break;
        default:
            return;
    }
}
    
bool Operation::isCorrectFor(unsigned y, unsigned x, unsigned S) const {
    switch (operation) {
        case UP:    return (y > 0);
        case DOWN:  return (y < (S - 1));
        case LEFT:  return (x > 0);
        case RIGHT: return (x < (S - 1));
        default:    return false;
    }
}

std::ostream & operator<< (std::ostream& out, const Operation & item) {
    out << Operation::opNames[item.operation];
    return out;
}