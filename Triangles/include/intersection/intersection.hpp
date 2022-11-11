#ifndef __INTERSEC__H__
#define __INTERSEC__H__

#include "primitives/triangle.hpp"
#include "primitives/vector.hpp"
#include <vector>
#include <algorithm>
#include <numeric>

namespace intersection {
std::vector<double> vec_to_matrix(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3);
std::vector<double> vec_to_matrix(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3, const geometry::vector_t &vec_4);

double calc_det(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3);
double calc_det(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3, const geometry::vector_t &vec_4);

std::array<int, 3> check_relative_pos(const geometry::triangle_t &tr_1, const geometry::triangle_t &tr_2);
std::array<int, 3> check_relative_pos(const geometry::vector_t &p_1, const geometry::triangle_t &tr_2);
bool intersection2D(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2);
bool intersection(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2);
void sort_triangles(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2, std::array<int, 3> &res_1, int sum_1);
bool intersec_first_step2D(std::array<int, 3> &res);
bool determine_region(const geometry::vector_t &p_1, std::array<int, 3> &res, geometry::triangle_t &tr_2);
bool solution_R1(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2);
bool solution_R2(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2);


} //nemaspace intersection

#endif //__INTERSEC__H__