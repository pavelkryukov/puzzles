#ifndef TASK_H
#define TASK_H

#include "blocklist.h"

class Task : public Coordinate, public BlockList {
public:
    // Count of unblocked digits
    const unsigned unBlocked;

    // Constructor
    inline Task(const int _y, 
        const int _x, const unsigned unBlocked_,
        const Coordinate & size, unsigned sugg)
        : Coordinate(_y, _x)
        , BlockList(sugg, _y, _x, size)
        , unBlocked(unBlocked_)
    { }

    // Comparsion for sorting
    inline const bool operator< (const Task & secondObj) {
        return (this->unBlocked < secondObj.unBlocked);
    }
};

#endif //TASK_H