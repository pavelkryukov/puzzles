#ifndef OPERATION_H
#define OPERATION_H

#include <ostream>

/*
 * Operation class
*/
class Operation {
private:

    enum EnumType {
        UP = 0,
        DOWN = 1,
        LEFT = 2,
        RIGHT = 3,
        NOVALID = 4
    };

    // Array of string names of operations
    static const char* const opNames[];

    // Array of next operations
    static const EnumType opNext[];

    // Array of anti operations
    static const EnumType opAnti[];

    // Current operation
    EnumType operation;
public:

    // Constructor
    inline Operation() { operation = UP; }

    void copy(const Operation & second);

    // Checks if current operation is valid
    inline const bool isValid() const { return operation != NOVALID; }

    bool operator!= (const Operation & secondObj) {
            return (this->operation == opAnti[secondObj.operation]);
        }
    
    // Make operation on this coordinates
    void operationMake(unsigned & y, unsigned & x) const;
    void operationUnMake(unsigned & y, unsigned & x) const;

    // Check if this operation can be made for this coordinates
    bool isCorrectFor(unsigned y, unsigned x, unsigned S) const;

    // Sets operation to next
    inline void operator++() {  operation = opNext[operation]; }

    // Dump operator
    friend std::ostream & operator<< (std::ostream& out, const Operation & item);
};

#endif