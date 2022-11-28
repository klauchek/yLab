#include "triangle.hpp"

namespace geometry {

vector_t triangle_t::get_vertex(int num) const {
    return vertices_[num];
}
size_t triangle_t::get_nvertex() const { 
    return vertices_.size();
}

//TODO: triangle is a struct now! no need for getters
std::ostream& operator<<(std::ostream &out, const triangle_t &triangle) {
    return out  << "[" << triangle.get_vertex(0) << "; " << triangle.get_vertex(1) << "; " << triangle.get_vertex(2) << "]" << std::endl;
}
std::istream& operator>>(std::istream &in, triangle_t &triangle) {
    return in  >> triangle.vertices_[0] >> triangle.vertices_[1] >> triangle.vertices_[2];
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
    if(cmp::dbl_cmp(det, 0.0) < 0)
        swap_qr();
    std::cout << "Det before" << det << std::endl;                     //
    det = common::calc_det(vertices_[0], vertices_[1], vertices_[2]);  //remove after debug
    std::cout << "Det after" << det << std::endl;                      //

}

//moving p_1 to ++- or to +-- part with circular permutation of T2
void triangle_t::circular_permutation(){
    std::swap(vertices_[0], vertices_[2]);   //циклическая перестановка, чтобы вывести p на нулевую позицию
    std::swap(vertices_[1], vertices_[2]);
}

void swap(triangle_t &first, triangle_t &second) {
    std::swap(first.vertices_[0], second.vertices_[0]);
    std::swap(first.vertices_[1], second.vertices_[1]);
    std::swap(first.vertices_[2], second.vertices_[2]);
    std::cout << "im here swap" << std::endl;
}

}