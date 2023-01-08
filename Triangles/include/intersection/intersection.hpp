#ifndef __INTERSEC__H__
#define __INTERSEC__H__

#include "primitives/triangle.hpp"
#include "primitives/vector.hpp"
#include "common/common.hpp"
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>

namespace intersection {

std::array<int, 3> check_relative_pos(const geometry::triangle_t &tr_1, const geometry::triangle_t &tr_2);
std::array<int, 3> check_relative_pos(const geometry::vector_t &p_1, const geometry::triangle_t &tr_2);
bool intersection2D(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2);
bool intersection(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2);
bool determine_side(geometry::vector_t &point, geometry::vector_t &a, geometry::vector_t &b, geometry::vector_t &c);
bool point_in_triangle(geometry::vector_t &point, geometry::vector_t &a, geometry::vector_t &b, geometry::vector_t &c);
std::pair<geometry::triangle_t, geometry::triangle_t> project_coplanar(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2);
void sort_triangles(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2, std::array<int, 3> &res_1, int sum_1);
bool intersec_first_step2D(std::array<int, 3> &res);
bool intersection_degenerate(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2);
bool det_signs_comp(double det_1, double det_2);
bool one_line_degenerates(geometry::vector_t &p1, geometry::vector_t &r1, geometry::vector_t &p2, geometry::vector_t &r2);
bool determine_region(const geometry::vector_t &p_1, std::array<int, 3> &res, geometry::triangle_t &tr_2);
bool solution_R1(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2);
bool solution_R2(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2);


} //namespace intersection

#endif //__INTERSEC__H__