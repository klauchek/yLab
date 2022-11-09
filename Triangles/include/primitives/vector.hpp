#ifndef __VECTOR__H__
#define __VECTOR__H__

#include <array>
#include <iostream>
#include <climits>

namespace geometry {

using point_t = double;

struct vector_t {
  
  std::array<point_t, 3> coords_;

  point_t get_coord(int num) const{
        if(num < 0 || num > 2)
            return 0;
        return coords_[num];
  }

  unsigned char relative_pos(const vector_t &other) const;

  vector_t operator/(double num);
  point_t &operator[](int num) { return coords_[num]; }
  const point_t &operator[](int num) const { return coords_[num]; }
};

vector_t operator+(const vector_t &first, const vector_t &second);
vector_t operator-(const vector_t &first, const vector_t &second);

std::ostream& operator<<(std::ostream &out, const vector_t &vec);

}

#endif //__VECTOR__H__
