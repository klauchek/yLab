#ifndef __VECTOR__H__
#define __VECTOR__H__

#include <array>
#include <iostream>
#include <climits>
#include <cmath>

namespace geometry {
using point_t = double;

struct vector_t final {
  
  std::array<point_t, 3> coords_;

  vector_t operator-() const;
  vector_t operator/(double num);
  unsigned char relative_pos(const vector_t &other) const;
  bool is_zero_vec();

  point_t &operator[](int num) { return coords_[num]; }
  const point_t &operator[](int num) const { return coords_[num]; }

};

double length(const vector_t &first, const vector_t &second);
vector_t cross_product(const vector_t &first, const vector_t &second);
double dot_product(const vector_t &first, const vector_t &second);

vector_t operator+(const vector_t &first, const vector_t &second);
vector_t operator-(const vector_t &first, const vector_t &second);

std::istream& operator>>(std::istream &in, vector_t &vec);
std::ostream& operator<<(std::ostream &out, const vector_t &vec);

} //namespace geometry

namespace cmp {

int dbl_cmp(const double x, const double y);

} //namespace cmp


#endif //__VECTOR__H__
