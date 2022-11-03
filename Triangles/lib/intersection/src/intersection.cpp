#include "../include/intersection.hpp"

namespace intersection {

//---------- DETERMINANTS CALCULATION ------------//
//             |a_x  a_y  1|
// [a, b, c]:= |b_x  b_y  1| = |a_x - c_x  a_y - c_y|
//             |c_x  c_y  1|   |b_x - c_x  b_y - c_y|
//
//                |a_x  a_y  a_z  1|   |a_x - d_x  a_y - d_y  a_z - d_z|
// [a, b, c, d]:= |b_x  b_y  b_z  1| = |b_x - d_x  b_y - d_y  b_z - d_z|
//                |c_x  c_y  c_z  1|   |c_x - d_x  c_y - d_y  c_z - d_z|
//                |d_x  d_y  d_z  1|
//------------------------------------------------//

std::vector<double> vec_to_matrix(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3) {
    geometry::vector_t new_vec_1 = vec_1 - vec_3;
    geometry::vector_t new_vec_2 = vec_2 - vec_3;
    std::vector<double> res{new_vec_1[0], new_vec_1[1],
                            new_vec_2[0], new_vec_2[1]};
    return res;
}
std::vector<double> vec_to_matrix(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3, const geometry::vector_t &vec_4) {
    geometry::vector_t new_vec_1 = vec_1 - vec_4;
    geometry::vector_t new_vec_2 = vec_2 - vec_4;
    geometry::vector_t new_vec_3 = vec_3 - vec_4;
    std::vector<double> res{new_vec_1[0], new_vec_1[1], new_vec_1[2],
                            new_vec_2[0], new_vec_2[1], new_vec_2[2],
                            new_vec_3[0], new_vec_3[1], new_vec_3[2]};
    return res;
}

double calc_det(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3) {
    std::vector<double> m = vec_to_matrix(vec_1, vec_2, vec_3);
    return m[0] * m[3] - m[1] * m[2];
}
double calc_det(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3, const geometry::vector_t &vec_4) {
    std::vector<double> m = vec_to_matrix(vec_1, vec_2, vec_3, vec_4);
    return m[0] * m[1 * 3 + 1] * m[2 * 3 + 2] +
        m[1] * m[1 * 3 + 2] * m[2 * 3] +
        m[2] * m[1 * 3]     * m[2 * 3 + 1] -
        m[2] * m[1 * 3 + 1] * m[2 * 3] -
        m[1] * m[1 * 3]     * m[2 * 3 + 2] -
        m[0] * m[1 * 3 + 2] * m[2 * 3 + 1];
}

//------------CHECKING SIGNS OF DETERMINANTS-----------//
// ... to determine if intersection is possible
//
// 1 is > 0, 0 if < 0
// 0 is [p2, q2, r2, p1] or [p1, q1, r1, p2]
// 1 is [p2, q2, r2, q1] or [p1, q1, r1, q2]
// 2 is [p2, q2, r2, r1] or [p1, q1, r1, r2]
// 
//-----------------------------------------------------//

std::array<int, 3> check_relative_pos(const geometry::triangle_t &tr_1, const geometry::triangle_t &tr_2) {  
    std::array<geometry::vector_t, 3> vertices_1{tr_1.get_vertex(0), tr_1.get_vertex(1), tr_1.get_vertex(2)};
    std::array<geometry::vector_t, 3> vertices_2{tr_2.get_vertex(0), tr_2.get_vertex(1), tr_2.get_vertex(2)};
    std::array<int, 3> res_arr;
    for(size_t i = 0; i < 3; ++i) {
        if(calc_det(vertices_1[0], vertices_1[1], vertices_1[2], vertices_2[i]) > 0)
            res_arr[i] = 1;
        if(calc_det(vertices_1[0], vertices_1[1], vertices_1[2], vertices_2[i]) < 0)
            res_arr[i] = -1;
        else
            res_arr[i] = 0;
    }
    return res_arr;
}

bool is_intersec_possible(int sum) {
    if(sum == 3 || sum == -3) {
        std::cout << "No intersection possible!" << std::endl;
        return false;
    }
    if(sum == 0) {
        std::cout << "We have 2D intersection!" << std::endl;
        return intersection2D(); ///??  returns true or false
    }
    return true;
}

bool intersection2D() {
    return true;
}

//const qualifiers??
bool intersection(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2) {
    std::array<int, 3> res_1 = check_relative_pos(tr_2, tr_1);
    int sum_1 = std::accumulate(res_1.begin(), res_1.end(), 0);
    if(!is_intersec_possible(sum_1))
        return false;

    std::array<int, 3> res_2 = check_relative_pos(tr_1, tr_2);
    int sum_2 = std::accumulate(res_2.begin(), res_2.end(), 0);
    if(!is_intersec_possible(sum_2))
        return false;
    
    sort_triangles(tr_1, tr_2, res_1, sum_1);

    ///to be continued
}

void sort_triangles(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2, std::array<int, 3> &res_1, int sum_1) {
    tr_1.set_p(res_1, sum_1);
    int sign = (calc_det(tr_2.get_vertex(0), tr_2.get_vertex(1), tr_2.get_vertex(2), tr_1.get_vertex(0)) > 0) ? 1 : -1;
    if(sign == -1)
        tr_2.swap_qr();
}



} //namespace intersection