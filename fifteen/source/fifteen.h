#ifndef FIFTEEN_H
#define FIFTEEN_H

#include <vector>
#include <fstream>
#include <ostream>
#include <string>

#include "operation.h"

class Fifteen : private std::vector<std::vector<unsigned> >{
private:
    // Size
    unsigned S_;
    
     // If true, position is correctly build
    bool isBuilt_;
        
    // ABS macro
    inline const static unsigned abs(const signed _a) { return (_a > 0) ? _a : (unsigned)(-_a); }

    // Coordinates of x and y
    unsigned x_;
    unsigned y_;    

    // Returns value of changes after operation
    // Less means better, bigger means worse
    const signed delta(const Operation & opType) const;

public:
    // Constructors
    Fifteen(unsigned S);
    Fifteen(std::istream & source);
    Fifteen(const Fifteen & source);

    // Hashes
    const std::string hash() const;

    bool isFinished() const;

    // Checks if this operation valid for current position
    const bool isValid(const Operation & opType) const {
        return opType.isCorrectFor(y_, x_, S_);
    }

    // Returns build status of position
    inline const bool isCorrect() const {
        return isBuilt_;
    }

    // Returns operation order vector
    // From best operation to worst
    void getListOfOperations(std::vector<Operation> & vector) const; 

    // Making of operation
    void   makeOperation(const Operation & opType);
    void unmakeOperation(const Operation & opType);

    // Dump
    friend std::ostream& operator<< (std::ostream & out, const Fifteen & item);
};

#endif