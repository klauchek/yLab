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



double calc_det(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3) {
    geometry::vector_t new_vec_1 = vec_1 - vec_3;
    geometry::vector_t new_vec_2 = vec_2 - vec_3;
    return new_vec_1[0] * new_vec_2[1] - new_vec_1[1] * new_vec_2[0];
}
double calc_det(const geometry::vector_t &vec_1, const geometry::vector_t &vec_2, const geometry::vector_t &vec_3, const geometry::vector_t &vec_4) {
    geometry::vector_t new_vec_1 = vec_1 - vec_4;
    geometry::vector_t new_vec_2 = vec_2 - vec_4;
    geometry::vector_t new_vec_3 = vec_3 - vec_4;
    double m_0 = new_vec_1[0];
    double m_1 = new_vec_1[1];
    double m_2 = new_vec_1[2];
    double m_3 = new_vec_2[0];
    double m_4 = new_vec_2[1];
    double m_5 = new_vec_2[2];
    double m_6 = new_vec_3[0];
    double m_7 = new_vec_3[1];
    double m_8 = new_vec_3[2];
    return m_0 * m_4 * m_8 +
        m_1 * m_5 * m_6 +
        m_2 * m_3 * m_7 -
        m_2 * m_4 * m_6 -
        m_1 * m_3 * m_8 -
        m_0 * m_5 * m_7;
}


}