#ifndef __INTERSEC__H__
#define __INTERSEC__H__

#include "../../primitives/include/plane.hpp"
#include "../../primitives/include/triangle.hpp"
#include "../../primitives/include/vector.hpp"
#include <vector>
#include <algorithm>
#include <numeric>

namespace intersection {
std::vector<double> vec_to_matrix(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3);
std::vector<double> vec_to_matrix(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3, const geometry::vector_t &vec_4);

double calc_det(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3);
double calc_det(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3, const geometry::vector_t &vec_4);

std::array<int, 3> check_relative_pos(const geometry::triangle_t &tr_1, const geometry::triangle_t &tr_2);
bool is_intersec_possible(int sum);
bool intersection2D();
bool intersection(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2);
void sort_triangles(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2, std::array<int, 3> &res_1, int sum_1);


} //nemaspace intersection

#endif //__INTERSEC__H__