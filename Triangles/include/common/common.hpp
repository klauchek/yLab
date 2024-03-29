#ifndef __COMMON__H__
#define __COMMON__H__

#include "primitives/vector.hpp"
#include <vector>

namespace common {

double calc_det(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3);
double calc_det(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3, const geometry::vector_t &vec_4);
double determinant (const geometry::vector_t &first, const geometry::vector_t &second, const geometry::vector_t &third);
} //namespace common


#endif //__COMMON__H__