#ifndef __TRIANGLE__H__
#define __TRIANGLE__H__

#include "vector.hpp"

namespace geometry {

class triangle_t {

    std::array<vector_t, 3> vertices_;

public:

    triangle_t();
    triangle_t(const vector_t &vec_1, const vector_t &vec_2, const vector_t &vec_3) : vertices_{vec_1, vec_2, vec_3} {}

    vector_t get_vertex(int num) const;
    size_t get_nvertex() const;
    void circular_permutation(std::array<int, 3> &res, int sign);
    void set_p(std::array<int, 3> &res, int sum);
    void swap_qr();
};

std::ostream& operator<<(std::ostream &out, const triangle_t &triangle);

}




#endif //__TRIANGLE__H__