#include "vector.hpp"

namespace geometry {

unsigned char vector_t::relative_pos(const vector_t &other) const {
	unsigned char res = 0;
	for(int i = 0; i < 3; ++i) {
		double cur_coord = other[i];
		if(cmp::dbl_cmp(cur_coord, coords_[i]) == 0) //TODO: double cmp
			return UCHAR_MAX;
		if(cmp::dbl_cmp(coords_[i], cur_coord) > 0)
			res |= (1 << i);
	}
	return res;
}

vector_t vector_t::operator-() const{
    return vector_t{-coords_[0], -coords_[1], -coords_[2]};
}

//TODO: think about [] 
vector_t operator+(const vector_t &first, const vector_t &second) {
    vector_t new_vec{first.get_coord(0) + second.get_coord(0),
                    first.get_coord(1) + second.get_coord(1),
                    first.get_coord(2) + second.get_coord(2)};
    return new_vec;
}

vector_t operator-(const vector_t &first, const vector_t &second) {
    vector_t new_vec{first.get_coord(0) - second.get_coord(0),
                    first.get_coord(1) - second.get_coord(1),
                    first.get_coord(2) - second.get_coord(2)};
    return new_vec;
}

vector_t vector_t::operator/(double num) {
    vector_t new_vec{coords_[0] / num, coords_[1] / num, coords_[2] / num};
    return new_vec;
}

double length(const vector_t &first, const vector_t &second) {
    double x = first.coords_[0] - second.coords_[0];
    double y = first.coords_[1] - second.coords_[1];
    double z = first.coords_[2] - second.coords_[2];

    return std::sqrt(x * x + y * y + z * z);
}

std::ostream& operator<<(std::ostream &out, const vector_t &vec) {
    return out  << "(" << vec.get_coord(0) << ", " << vec.get_coord(1) << ", " << vec.get_coord(2) << ")";
}
std::istream& operator>>(std::istream &in, vector_t &vec) {
    return in >> vec.coords_[0] >> vec.coords_[1] >> vec.coords_[2];
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
