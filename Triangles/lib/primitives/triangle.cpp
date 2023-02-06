#include "triangle.hpp"

namespace geometry {

size_t triangle_t::get_nvertex() const { 
    return vertices_.size();
}

std::ostream& operator<<(std::ostream &out, const triangle_t &triangle) {
    return out  << "[" << triangle[0] << "; " << triangle[1] << "; " << triangle[2] << "]" << std::endl;
}
std::istream& operator>>(std::istream &in, triangle_t &triangle) {
    return in  >> triangle[0] >> triangle[1] >> triangle[2];
}

//-----------------------------------------------//
//---------- FUNCTIONS FOR 3D INTERSECTION ------//
//-----------------------------------------------//

//moving p point to 0 position
void triangle_t::circular_permutation(const std::array<int, 3> &res, int sign){
    if(res[0] == sign)
        return;
    std::swap(vertices_[0], vertices_[2]);
    int a = (res[1] != sign);
    std::swap(vertices_[0 + a], vertices_[1 + a]);
}

void triangle_t::set_p(const std::array<int, 3> &res, int sum) {
    if(sum == 0)
        circular_permutation(res, -1);    
    if(sum == 1) {
        if(std::count(res.begin(), res.end(), 0) == 2)
            circular_permutation(res, 1);
        else
            circular_permutation(res, -1);
    }
    if(sum == -1) {
        if(std::count(res.begin(), res.end(), 0) == 2)
            circular_permutation(res, -1);
        else
            circular_permutation(res, 1);
    }
    if(sum == 2 || sum == -2)
        circular_permutation(res, 0);
}
void triangle_t::swap_qr() {
    std::swap(vertices_[1], vertices_[2]);
}

//-----------------------------------------------//
//---------- FUNCTIONS FOR 2D INTERSECTION ------//
//-----------------------------------------------//

void triangle_t::counter_clock() {
    double det = common::calc_det(vertices_[0], vertices_[1], vertices_[2]);
    if(cmp::dbl_cmp(det, 0.0) < 0)
        swap_qr();
}

//moving p_1 to ++- or to +-- part with circular permutation of T2
void triangle_t::circular_permutation(){
    std::swap(vertices_[0], vertices_[2]);
    std::swap(vertices_[1], vertices_[2]);
}

void triangle_t::coords_circular_permutation(){
    for(int i = 0; i < 3; ++i) {
        std::swap(vertices_[i][0], vertices_[i][2]);
        std::swap(vertices_[i][1], vertices_[i][2]);
    }
}

void swap(triangle_t &first, triangle_t &second) {
    std::swap(first[0], second[0]);
    std::swap(first[1], second[1]);
    std::swap(first[2], second[2]);
}

//--------------------------------------------------------//
//---------- FUNCTIONS FOR DEGENERATES INTERSECTION ------//
//--------------------------------------------------------//

void triangle_t::line_counter_clock() {
    double len_1 = length(vertices_[0], vertices_[2]);
    double len_2 = length(vertices_[0], vertices_[1]);
    double len_3 = length(vertices_[1], vertices_[2]);

    double max_1 = std::max(len_1, len_2);
    double max_2 = std::max(max_1, len_3);

    if(max_2 == len_1) 
        return;
    if(max_2 == len_2) {
        std::swap(vertices_[1], vertices_[2]);
        return;
    }
    if(max_2 == len_3) { 
        std::swap(vertices_[0], vertices_[1]);
        return;
    }

}

}