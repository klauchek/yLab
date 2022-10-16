#include "../include/vector.hpp"

namespace geometry {

unsigned char vector_t::relative_pos(const vector_t &other) const {
	unsigned char res = 0;
	for(int i = 0; i < 3; ++i) {
		double cur_coord = other[i];
		if(cur_coord == coords_[i]) //TODO: double cmp
			return UCHAR_MAX;
		if(coords_[i] > cur_coord)
			res |= (1 << i);
	}
	return res;
}

vector_t operator+(const vector_t &first, const vector_t &second) {
    vector_t new_vec{first.get_coord(0) + second.get_coord(0),
                    first.get_coord(1) + second.get_coord(1),
                    first.get_coord(2) + second.get_coord(2)};
    return new_vec;
}

vector_t vector_t::operator/(double num) {
    vector_t new_vec{coords_[0] / num, coords_[1] / num, coords_[3] / num};
    return new_vec;
}

std::ostream& operator<<(std::ostream &out, const vector_t &vec) {
    return out  << "(" << vec.get_coord(0) << ", " << vec.get_coord(1) << ", " << vec.get_coord(2) << ")";
}

}
