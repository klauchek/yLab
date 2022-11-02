#ifndef __INTERSEC__H__
#define __INTERSEC__H__

#include "../../primitives/include/plane.hpp"
#include "../../primitives/include/triangle.hpp"
#include "../../primitives/include/vector.hpp"
#include <vector>

/*
struct pqr{
    p
    q
    r
}
*/

std::vector<double> vec_to_matrix(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3);
std::vector<double> vec_to_matrix(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3, const geometry::vector_t &vec_4);

double calc_det(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3);
double calc_det(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3, const geometry::vector_t &vec_4);
/* 
checking signs of determinants: 1 is > 0, 0 if < 0
0 is [p2, q2, r2, p1] or [p1, q1, r1, p2]
1 is [p2, q2, r2, q1] or [p1, q1, r1, q2]
2 is [p2, q2, r2, r1] or [p1, q1, r1, r2]
*/
//unsigned char* check_relative_pos(const geometry::plane_t &plane, const geometry::triangle_t &tr);


// }

#endif //__INTERSEC__H__