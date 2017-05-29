#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate {
public:
    const int y;
    const int x;
    inline Coordinate( const int _y, const int _x)
        : y(_y)
        , x(_x)
    { }
};

#endif //COORDINATE_H