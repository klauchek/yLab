#ifndef __TRIANGLE__H__
#define __TRIANGLE__H__

#include "vector.hpp"
#include "common/common.hpp"
#include <vector>

namespace geometry {

struct triangle_t {

    std::array<vector_t, 3> vertices_;

    triangle_t(){}
    triangle_t(const vector_t &vec_1, const vector_t &vec_2, const vector_t &vec_3) : vertices_{vec_1, vec_2, vec_3} {}

    vector_t get_vertex(int num) const;
    size_t get_nvertex() const;
    void circular_permutation(std::array<int, 3> &res, int sign);
    void circular_permutation();
    void counter_clock();
    void set_p(std::array<int, 3> &res, int sum);
    void swap_qr();
};

std::ostream& operator<<(std::ostream &out, const triangle_t &triangle);
std::istream& operator>>(std::istream &in, triangle_t &triangle);
void swap(triangle_t &first, triangle_t &second);

}




#endif //__TRIANGLE__H__