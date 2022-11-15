#include "triangle.hpp"

namespace geometry {

vector_t triangle_t::get_vertex(int num) const {
    return vertices_[num];
}
size_t triangle_t::get_nvertex() const { 
    return vertices_.size();
}
std::ostream& operator<<(std::ostream &out, const triangle_t &triangle) {
    return out  << "[" << triangle.get_vertex(0) << "; " << triangle.get_vertex(1) << "; " << triangle.get_vertex(2) << "]" << std::endl;
}

//-----------------------------------------------//
//---------- FUNCTIONS FOR 3D INTERSECTION ------//
//-----------------------------------------------//
void triangle_t::circular_permutation(std::array<int, 3> &res, int sign){
    if(res[0] == sign)
        return;
    std::swap(vertices_[0], vertices_[2]);   //циклическая перестановка, чтобы вывести p на нулевую позицию
    if(res[1] == sign)
        std::swap(vertices_[0], vertices_[1]);
    else
        std::swap(vertices_[1], vertices_[2]);
}

void triangle_t::set_p(std::array<int, 3> &res, int sum) {
    if(sum == 1)
        circular_permutation(res, -1);
    if(sum == -1)
        circular_permutation(res, 1);
    if(sum == 2 || sum == -2)
        circular_permutation(res, 0);
}
void triangle_t::swap_qr() {
    std::cout << "swap happened" << std::endl;
    std::swap(vertices_[1], vertices_[2]);
}

//-----------------------------------------------//
//---------- FUNCTIONS FOR 2D INTERSECTION ------//
//-----------------------------------------------//

void triangle_t::counter_clock() {
    double det = common::calc_det(vertices_[0], vertices_[1], vertices_[2]);
    if(det < 0)
        swap_qr();
    std::cout << "Det before" << det << std::endl;
    det = common::calc_det(vertices_[0], vertices_[1], vertices_[2]);
    std::cout << "Det after" << det << std::endl;

}


//moving p_1 to ++- or to +-- part with circular permutation of T2
void triangle_t::circular_permutation(){
    std::swap(vertices_[0], vertices_[2]);   //циклическая перестановка, чтобы вывести p на нулевую позицию
    std::swap(vertices_[1], vertices_[2]);
}

}