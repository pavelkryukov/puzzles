#ifndef BLOCKLIST_H
#define BLOCKLIST_H

#include <list>

#include "coordinate.h"

class BlockList : public std::list<Coordinate> {
public:
    unsigned digit;
    BlockList(unsigned digit, unsigned y, unsigned x, const Coordinate & size);
};

#endif // BLOCKLIST_H
