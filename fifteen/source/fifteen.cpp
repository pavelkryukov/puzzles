#include <cstdlib>

#include <set>

#include <puzzle/reorderer.h>

#include "fifteen.h"

// Key method of whole program
// Returns value of changes after operation
// Less means better, bigger means worse
const signed Fifteen::delta(const Operation & opType) const {
    // Coordinates of moving item
    unsigned y1 = y_;
    unsigned x1 = x_;
    opType.operationMake(y1, x1);

    // Moving item digit
    const unsigned digit = (*this)[y1][x1];

    // Coordinates of final position of moving item
    const unsigned y2 = (digit - 1) / S_;
    const unsigned x2 = (digit - 1) % S_;


    // Movement of void cell
    // If it's moved closer to bottom right corner, it's less than 0.
    // Otherwise it's greater.
    const signed delta_void = abs(S_ - y_ - 1) + abs(S_ - x_ - 1) - abs(S_ - y1 - 1) - abs(S_ - x1 - 1);

    // Priority of item.
    // First we should dispatch squares near top left corner
//  const unsigned priority = (S_*S_ - digit);
    const unsigned priority = (S_*S_ - (y2 + 1) * (x2 + 1));


    // Length before moving between current position and final
    const unsigned length_before = abs(y2 - y1) + abs(x2 - x1);
    
    // if length_before == 0, moving is not so necessary
    // S_ * S_ is much greater than any length delta
    if (!length_before) 
        return (-1) * S_ * S_ * priority * (2 - delta_void);

    // Length after moving between current position and final
    const unsigned length_after = abs(y2 - y_) + abs(x2 - x_);

    // if length_after == 0, moving is very necessary
    if (!length_after)
        return (S_ * S_) * priority * (2 + delta_void);

    // Returning delta multiplied to priority
    // If delta < 0, cell become closer to final position
    const signed delta = (length_after - length_before) * 2 - delta_void;

    return (-1) * delta * priority; 
}

// Zero constructor
// Constructs solved puzzle
Fifteen::Fifteen(unsigned S) : std::vector<std::vector<unsigned> >(S, std::vector<unsigned>(S)), S_(S) {
    for ( unsigned j = 1, i = 0; i < S_; i++) {
        for ( unsigned l = 0; (l < S_) && (j < S_*S_); j++, l++) {
            (*this)[i][l] = j;
        }
    }
    this->x_ = S_ - 1;
    this->y_ = S_ - 1;
}

// Constructor from file
Fifteen::Fifteen(std::istream & source) {
    std::string buffer;
    std::getline(source, buffer);

    S_ = std::atoi(buffer.c_str());
    this->resize(S_, std::vector<unsigned>(S_));

    std::set<unsigned> nonUsedNumbers;
    for (unsigned i = 0; i < S_*S_; i++) {
        nonUsedNumbers.insert(i);
    }
    for ( unsigned i = 0; i < S_; i++) {
        std::string buffer;
        std::getline(source, buffer);
        for ( unsigned j = 0; j < S_; j++) {
            unsigned number;
            if ((buffer[j] >= '1') && (buffer[j] <= '9')) {
                number = (buffer[j] - '1') + 1;
            } 
            else if ((buffer[j] >= 'A') && (buffer[j] <= 'Z')) {
                number = (buffer[j] - 'A') + 10;
            }
            else 
            {
                number = 0;
                this->x_ = j;
                this->y_ = i;
            }
            std::set<unsigned>::iterator findedNumber = nonUsedNumbers.find(number);
            if (findedNumber == nonUsedNumbers.end()) {
                isBuilt_ = false;
                return;
            } 
            (*this)[i][j] = number;
            nonUsedNumbers.erase(number);
        }
    }
    if (nonUsedNumbers.size() != 0) {
        isBuilt_ = false;
        return;
    }
    isBuilt_ = true;
}

// Copy constructor
Fifteen::Fifteen(const Fifteen & source) :       
        std::vector<std::vector<unsigned> >(source),
                                         S_(source.S_),
                                   isBuilt_(source.isBuilt_),
                                         x_(source.x_),y_(source.y_) {}

// Return hash of current position
const std::string Fifteen::hash() const {
    std::string hash;
    for (unsigned i = 0; i < S_; i++) {
        for (unsigned j = 0; j < S_; j++) {
            hash += (*this)[i][j] + 'A';
        }
    }
    return hash;
}

// Returns hash of standart final position for S size
bool Fifteen::isFinished() const {
    unsigned l = 1;
    for (unsigned i = 0; i < S_; i++) {
        for (unsigned j = 0; j < S_; j++) {
            if ((i == j) && (i == S_ - 1))
                break;
            if ((*this)[i][j] != l++)
                return false;
        }
    }
    return true;
}

// Returns operation order vector
// From best operation to worst
void Fifteen::getListOfOperations(std::vector<Operation> & vector) const {  
    // Reordering list
    OperationOrderList<Operation, signed> sortBuffer;

    // Filling list with only valid operations and their priorities
    for (Operation opType; opType.isValid(); ++opType) {
        if (this->isValid(opType)) {
           sortBuffer.push_back(opType, this->delta(opType));
        }
    }
    
    sortBuffer.getVector(vector);
}

// Making movement
void Fifteen::makeOperation(const Operation & type) {

    unsigned y1 = y_;
    unsigned x1 = x_;
    type.operationMake(y1, x1);

    (*this)[y_][x_] = (*this)[y1][x1];
    (*this)[y1][x1] = 0;
    y_ = y1;
    x_ = x1;
}

void Fifteen::unmakeOperation(const Operation & type) {

    unsigned y1 = y_;
    unsigned x1 = x_;
    type.operationUnMake(y1, x1);

    (*this)[y_][x_] = (*this)[y1][x1];
    (*this)[y1][x1] = 0;
    y_ = y1;
    x_ = x1;
}

// Dump
std::ostream & operator<< (std::ostream & out, const Fifteen & item) {
    for (unsigned i = 0; i < item.S_; i++) {
        out << std::endl;
        for (unsigned j = 0; j < item.S_; j++) {
            out << "[" << item[i][j] << "] ";
        }
    }
    return out;
}