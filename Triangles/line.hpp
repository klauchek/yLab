#ifndef LINE_H
#define LINE_H

#include "vector.hpp"

class Line
{
private:
//dir vector
    Vector d_;
    Vector r0_;

public:
    Line(Vector& r0, Vector& d): r0_(r0),
                                d_(d)
    {}
    Line(): r0_(0, 0, 0),
            d_(0, 0, 0)
    {}

}


#endif