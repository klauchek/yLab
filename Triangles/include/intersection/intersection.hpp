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

//--------------------- 3D INTERSECTION ---------------------//
std::array<int, 3> check_relative_pos(const geometry::triangle_t &tr_1, const geometry::triangle_t &tr_2);
bool point_in_triangle(const geometry::vector_t &point, const geometry::triangle_t &tr);
bool one_common_point_3D(const std::array<int, 3> &res, const geometry::triangle_t &tr_1, const geometry::triangle_t &tr_2);
void sort_triangles(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2, const std::array<int, 3> &res_1, int sum_1);
bool intersection(geometry::triangle_t tr_1, geometry::triangle_t tr_2);

//--------------------- 2D INTERSECTION ---------------------//
std::array<int, 3> check_relative_pos(const geometry::vector_t &p_1, const geometry::triangle_t &tr_2);
std::pair<geometry::triangle_t, geometry::triangle_t> projection(const geometry::triangle_t &tr_1, const geometry::triangle_t &tr_2, size_t axe_1, size_t axe_2);
std::pair<geometry::triangle_t, geometry::triangle_t> project_coplanar(const geometry::triangle_t &tr_1, const geometry::triangle_t &tr_2);
bool intersection2D(geometry::triangle_t tr_1, geometry::triangle_t tr_2);

//------------------ DEGENERATE INTERSECTION ---------------//
bool intersection_triangle_degenerate(geometry::triangle_t tr_1, geometry::triangle_t tr_2);
bool intersection_degenerate(geometry::triangle_t tr_1, geometry::triangle_t tr_2);
bool one_line_degenerates(const geometry::vector_t &p1, const geometry::vector_t &r1, const geometry::vector_t &p2, const geometry::vector_t &r2);

//-------------------------- OTHER ------------------------//

bool det_signs_comp(double det_1, double det_2);
} //namespace intersection

#endif //__INTERSEC__H__