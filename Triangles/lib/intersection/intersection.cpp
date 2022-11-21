#include "intersection.hpp"

namespace intersection {

// TODO: make common and remove from triangle



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
        double det = common::calc_det(vertices_1[0], vertices_1[1], vertices_1[2], vertices_2[i]);
        int sign = cmp::dbl_cmp(det, 0.0);
        if(sign > 0)
            res_arr[i] = 1;
        else if(sign < 0) //вынести
            res_arr[i] = -1;
        else
            res_arr[i] = 0;
    }
    for(auto u : res_arr)
        std::cout << u << " ";
    std::cout << std::endl; 
    return res_arr;
}

//-----------------------------------------------------//
//------------------ 3D INTERSECTION ------------------//
//---------------------------------------------------- //
//const qualifiers??
bool intersection(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2) {
    std::array<int, 3> res_1 = check_relative_pos(tr_2, tr_1);
    int sum_1 = std::accumulate(res_1.begin(), res_1.end(), 0);

    std::array<int, 3> res_2 = check_relative_pos(tr_1, tr_2);
    int sum_2 = std::accumulate(res_2.begin(), res_2.end(), 0);

    if((sum_1 == 3 || sum_1 == -3) || (sum_2 == 3 || sum_2 == -3)) {
        std::cout << "No intersection possible!" << std::endl;
        return false;
    }
    if(sum_1 == 0 || sum_2 == 0) {
        std::cout << "sum_1: " << sum_1 << " sum 2: " << sum_2 << std::endl;
        std::cout << "We have 2D intersection!" << std::endl;
        return intersection2D(tr_1, tr_2);
    }

    sort_triangles(tr_1, tr_2, res_1, sum_1);
    sort_triangles(tr_2, tr_1, res_2, sum_2);

    if((sum_1 == 2 || sum_2 == 2) || (sum_1 == -2 || sum_2 == -2)) {
        std::cout << "im here! 1" << std::endl;
        return true;
    }

    std::array<geometry::vector_t, 3> vertices_1{tr_1.get_vertex(0), tr_1.get_vertex(1), tr_1.get_vertex(2)};
    std::array<geometry::vector_t, 3> vertices_2{tr_2.get_vertex(0), tr_2.get_vertex(1), tr_2.get_vertex(2)};

    if(cmp::dbl_cmp(common::calc_det(vertices_1[0], vertices_1[1], vertices_2[1], vertices_2[0]), 0.0) >= 0 
        && cmp::dbl_cmp(common::calc_det(vertices_1[0], vertices_1[2], vertices_2[2], vertices_2[0]), 0.0) <= 0)
            return true;
    return false;
}

void sort_triangles(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2, std::array<int, 3> &res_1, int sum_1) {
    tr_1.set_p(res_1, sum_1);
    int sign = (cmp::dbl_cmp(common::calc_det(tr_2.get_vertex(0), tr_2.get_vertex(1), tr_2.get_vertex(2), tr_1.get_vertex(0)), 0.0) > 0) ? 1 : -1;
    if(sign == -1)
        tr_2.swap_qr();
}

//-----------------------------------------------------//
//------------------ 2D INTERSECTION ------------------//
//---------------------------------------------------- //
bool intersection2D(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2) {
    tr_1.counter_clock();
    tr_2.counter_clock();

    geometry::vector_t p_1 = tr_1.get_vertex(0);
    std::array<int, 3> res = check_relative_pos(p_1, tr_2);

    std::cout << "res: " << res[0] << ", " << res[1] << ", " << res[2] << std::endl;
    if(intersec_first_step2D(res))
        return true;
    
    //other cases - moving p_1 to ++- or to +-- part with circular permutation of T2
    // + means det >= 0; - means det < 0;
    // [p1, p2, q2]
    // [p1, q2, r2]
    // [p1, r2, p2]

    if(determine_region(p_1, res, tr_2)) {
        std::cout << "We go to R1! - edge intersection" << std::endl;
        return solution_R1(tr_1, tr_2);
    }
    else {
        std::cout << "We go to R2! - vertex intersection" << std::endl;
        return solution_R2(tr_1, tr_2);
    }

    return false;
}

std::array<int, 3> check_relative_pos(const geometry::vector_t &p_1, const geometry::triangle_t &tr_2) {
    std::array<geometry::vector_t, 3> vertices_2{tr_2.get_vertex(0), tr_2.get_vertex(1), tr_2.get_vertex(2)};
    std::array<int, 3> res_arr;

    for(size_t i = 0; i < 3; ++i) {
        double det = common::calc_det(p_1, vertices_2[i], vertices_2[(i + 1) % 3]);
        std::cout << "det = " << det << std::endl;
        double res_cmp = cmp::dbl_cmp(det, 0);
        std::cout << "res_cmp = " << res_cmp << std::endl;
        if(cmp::dbl_cmp(res_cmp, 0.0) > 0)
            res_arr[i] = 1;
        else if(cmp::dbl_cmp(res_cmp, 0.0) < 0)
            res_arr[i] = -1;
        else
            res_arr[i] = 0;
    }
    return res_arr;
}

//const???
bool intersec_first_step2D(std::array<int, 3> &res) {
    int num_zeros = std::count(res.begin(), res.end(), 0);
    int num_ones = std::count(res.begin(), res.end(), 1);
    if(num_ones == 3) {
        std::cout << "p1 is in T2!" << std::endl;
        return true;
    }
    if(num_zeros == 2) {
        std::cout << "p1 is on the vertex of T2!" << std::endl;
        return true;
    }
    if(num_zeros == 1 && num_ones == 2) {
        std::cout << "p1 is on the edge of T2!" << std::endl;
        return true;
    }
    if(num_zeros == 3) {
        //
    }
    return false;
}

// --- check if p` is in ++- part +--
namespace {
bool check_R1(std::array<int, 3> &res) {
    if(res[0] >= 0 && res[1] >= 0 && res[2] < 0)
        return true;
    return false;
}
bool check_R2(std::array<int, 3> &res) {
    if(res[0] >= 0 && res[1] < 0 && res[2] < 0)
        return true;
    return false;
}
}

bool determine_region(const geometry::vector_t &p_1, std::array<int, 3> &res, geometry::triangle_t &tr_2) {
    bool R1 = check_R1(res);
    bool R2 = check_R2(res);
    while(R1 != 1 && R2 != 1) {
        std::cout << "im here" << std::endl;
        tr_2.circular_permutation();
        std::cout << tr_2;
        res = check_relative_pos(p_1, tr_2);
        for(auto v : res)
            std::cout << v << " ";
        std::cout << std::endl;
        R1 = check_R1(res);
        R2 = check_R2(res);   
    }
    return R1;
}

bool solution_R1(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2){
    std::array<geometry::vector_t, 3> vrts_1{tr_1.get_vertex(0), tr_1.get_vertex(1), tr_1.get_vertex(2)}; // p1, q1, r1
    std::array<geometry::vector_t, 3> vrts_2{tr_2.get_vertex(0), tr_2.get_vertex(1), tr_2.get_vertex(2)}; // p2, q2, r2

    if(cmp::dbl_cmp(common::calc_det(vrts_2[2], vrts_2[0], vrts_1[1]), 0.0) >= 0) {
        if(cmp::dbl_cmp(common::calc_det(vrts_1[0], vrts_2[0], vrts_1[1]), 0.0) >= 0) {
            if(cmp::dbl_cmp(common::calc_det(vrts_1[0], vrts_1[1], vrts_2[2]), 0.0) >= 0)
                return 1;
        }
        else {
            if(cmp::dbl_cmp(common::calc_det(vrts_1[1], vrts_1[2], vrts_2[0]), 0.0) >= 0) {
                if(cmp::dbl_cmp(common::calc_det(vrts_1[2], vrts_1[0], vrts_2[0]), 0.0) >= 0)
                    return 1;
            }
        }
    }
    else {
        if(cmp::dbl_cmp(common::calc_det(vrts_2[2], vrts_2[0], vrts_1[2]), 0.0) >= 0) {
            if(cmp::dbl_cmp(common::calc_det(vrts_1[0], vrts_2[0], vrts_1[2]), 0.0) >= 0) {
                if(cmp::dbl_cmp(common::calc_det(vrts_1[0], vrts_1[2], vrts_2[2]), 0.0) >= 0)
                    return 1;
                if(cmp::dbl_cmp(common::calc_det(vrts_1[1], vrts_1[2], vrts_2[2]), 0.0) >= 0)
                    return 1;
            }
        }
    }
    return 0;    
}

bool solution_R2(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2){
    std::array<geometry::vector_t, 3> vrts_1{tr_1.get_vertex(0), tr_1.get_vertex(1), tr_1.get_vertex(2)}; // p1, q1, r1
    std::array<geometry::vector_t, 3> vrts_2{tr_2.get_vertex(0), tr_2.get_vertex(1), tr_2.get_vertex(2)}; // p2, q2, r2

    if(cmp::dbl_cmp(common::calc_det(vrts_2[2], vrts_2[0], vrts_1[1]), 0.0) >= 0) {
        if(cmp::dbl_cmp(common::calc_det(vrts_2[2], vrts_2[1], vrts_1[1]), 0.0) <= 0) {
            if(cmp::dbl_cmp(common::calc_det(vrts_1[0], vrts_2[0], vrts_1[1]), 0.0) > 0) {
                if(cmp::dbl_cmp(common::calc_det(vrts_1[0], vrts_2[1], vrts_1[1]), 0.0) <= 0)
                    return 1;
            }
            else {
                if(cmp::dbl_cmp(common::calc_det(vrts_1[0], vrts_2[0], vrts_1[2]), 0.0) >= 0) {
                    if(cmp::dbl_cmp(common::calc_det(vrts_1[1], vrts_1[2], vrts_2[0]), 0.0) >= 0)
                        return 1;
                }
            }
        }
        else {
            if(cmp::dbl_cmp(common::calc_det(vrts_1[0], vrts_2[1], vrts_1[1]), 0.0) <= 0) {
                if(cmp::dbl_cmp(common::calc_det(vrts_2[2], vrts_2[1], vrts_1[2]), 0.0) <= 0) {
                    if(cmp::dbl_cmp(common::calc_det(vrts_1[1], vrts_1[2], vrts_2[1]), 0.0) >= 0)
                        return 1;
                }
            }
        }
    }
    else {
        if(cmp::dbl_cmp(common::calc_det(vrts_2[2], vrts_2[0], vrts_1[2]), 0.0) >= 0) {
            if(cmp::dbl_cmp(common::calc_det(vrts_1[1], vrts_1[2], vrts_2[2]), 0.0) >= 0) {
                if(cmp::dbl_cmp(common::calc_det(vrts_1[0], vrts_2[0], vrts_1[2]), 0.0) >= 0)
                    return 1;
            }
            else {
                if(cmp::dbl_cmp(common::calc_det(vrts_1[1], vrts_1[2], vrts_2[1]), 0.0) >= 0) {
                    if(cmp::dbl_cmp(common::calc_det(vrts_2[2], vrts_1[2], vrts_2[1]), 0.0) >= 0)
                        return 1;
                }
            }
        }
    }
    return 0;
}

} //namespace intersection