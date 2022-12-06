#include "common.hpp"

namespace common {

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
    // std::cout << m[0] << "  " << m[1] << std::endl 
    //           << m[2] << "  " << m[3] << std::endl;
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


}