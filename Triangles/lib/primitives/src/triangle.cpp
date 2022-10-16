#include "../include/triangle.hpp"

namespace geometry {

vector_t triangle_t::get_vertex(int num) const{
    return vertices_[num];
}
std::ostream& operator<<(std::ostream &out, const triangle_t &triangle) {
    return out  << "[" << triangle.get_vertex(0) << "; " << triangle.get_vertex(1) << "; " << triangle.get_vertex(2) << "]" << std::endl;
}

}