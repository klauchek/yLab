#include "vector.hpp"

namespace geometry {

unsigned char vector_t::relative_pos(const vector_t &other) const {
	unsigned char res = 0;
	for(int i = 0; i < 3; ++i) {
		double cur_coord = other[i];
		if(cmp::dbl_cmp(cur_coord, coords_[i]) == 0)
			return UCHAR_MAX;
		if(cmp::dbl_cmp(coords_[i], cur_coord) > 0)
			res |= (1 << i);
	}
	return res;
}

vector_t vector_t::operator-() const{
    return vector_t{-coords_[0], -coords_[1], -coords_[2]};
}

vector_t operator+(const vector_t &first, const vector_t &second) {
    vector_t new_vec{first[0] + second[0],
                    first[1] + second[1],
                    first[2] + second[2]};
    return new_vec;
}

vector_t operator-(const vector_t &first, const vector_t &second) {
    vector_t new_vec{first[0] - second[0],
                    first[1] - second[1],
                    first[2] - second[2]};
    return new_vec;
}

vector_t vector_t::operator/(double num) {
    vector_t new_vec{coords_[0] / num, coords_[1] / num, coords_[2] / num};
    return new_vec;
}

bool vector_t::is_zero_vec() {
    if(cmp::dbl_cmp(coords_[0], 0) == 0 && cmp::dbl_cmp(coords_[1], 0) == 0 && cmp::dbl_cmp(coords_[2], 0) == 0)
        return true;
    return false;
}

double length(const vector_t &first, const vector_t &second) {
    double x = first[0] - second[0];
    double y = first[1] - second[1];
    double z = first[2] - second[2];

    return std::sqrt(dot_product({x, y, z}, {x, y, z}));
}

vector_t cross_product(const vector_t &first, const vector_t &second) {
    vector_t new_vec { first[1] * second[2] - first[2] * second[1],
                    first[2] * second[0] - first[0] * second[2],
                    first[0] * second[1] - first[1] * second[0]};
    return new_vec;
}

double dot_product(const vector_t &first, const vector_t &second) {
    return first[0] * second[0] + first[1] * second[1] + first[2] * second[2];
}

std::ostream& operator<<(std::ostream &out, const vector_t &vec) {
    return out  << "(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")";
}
std::istream& operator>>(std::istream &in, vector_t &vec) {
    return in >> vec[0] >> vec[1] >> vec[2];
}

}//namespace geometry

namespace cmp {

int dbl_cmp(const double x, const double y) {
    const double epsilon = 10E-6;

    if (std::abs(x - y) < epsilon)
        return 0;
    if (x - y > 0)
        return 1;
    return -1;
}

}//namespace cmp
