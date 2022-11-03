#include "../include/triangle.hpp"

namespace geometry {

vector_t triangle_t::get_vertex(int num) const {
    return vertices_[num];
}
size_t triangle_t::get_nvertex() const { 
    return vertices_.size();
}

//res = [p q r] --> 
void triangle_t::set_p(std::array<int, 3> &res, int sum) {
    if(sum == 2) {
        if(res[0] == -1)
            return;
        std::swap(vertices_[0], vertices_[2]);   //циклическая перестановка, чтобы вывести p на нулевую позицию
        if(res[1] == -1)
            std::swap(vertices_[0], vertices_[1]);
        else
            std::swap(vertices_[1], vertices_[2]);
    }
    if(sum == -2) {
        if(res[0] == 1)
            return;
        std::swap(vertices_[0], vertices_[2]);   //циклическая перестановка, чтобы вывести p на нулевую позицию
        if(res[1] == 1)
            std::swap(vertices_[0], vertices_[1]);
        else
            std::swap(vertices_[1], vertices_[2]);
    }
    //! TODO   ОБОБЩИТЬ
}
void triangle_t::swap_qr() {
    std::swap(vertices_[1], vertices_[2]);
}

std::ostream& operator<<(std::ostream &out, const triangle_t &triangle) {
    return out  << "[" << triangle.get_vertex(0) << "; " << triangle.get_vertex(1) << "; " << triangle.get_vertex(2) << "]" << std::endl;
}

}