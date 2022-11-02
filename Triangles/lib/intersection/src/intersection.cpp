#include "../include/intersection.hpp"

/*
struct pqr{
    p
    q
    r
}
*/

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

/* 
checking signs of determinants: 1 is > 0, 0 if < 0
0 is [p2, q2, r2, p1] or [p1, q1, r1, p2]
1 is [p2, q2, r2, q1] or [p1, q1, r1, q2]
2 is [p2, q2, r2, r1] or [p1, q1, r1, r2]
*/
// unsigned char* check_relative_pos(const geometry::plane_t &plane, const geometry::triangle_t &tr) {  
//     //calc_det();
// }

// bool intersection() {
//     check_relative_pos(plane2, tr1);
//     check_relative_pos(plane1, tr2);

//     pair<pqr, pqr> sorts_trs(tr1, tr2) {
//         get p //метод треугольника??
//         swap_qr
//     }
    


// }