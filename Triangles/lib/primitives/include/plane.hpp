#ifndef __PLANE__H__
#define __PLANE__H__

#include "vector.hpp"

namespace geometry {

class plane_t {

    vector_t norm_;
    double d_;

public:

    //plane equation: n * x + d = 0, x - any point on plane
    plane_t(const vector_t &norm, double d) : norm_(norm), d_(d) {}

};

std::ostream& operator<<(std::ostream &out, const plane_t &plane);

}




#endif //__PLANE__H__