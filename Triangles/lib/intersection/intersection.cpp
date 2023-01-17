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
    std::array<geometry::vector_t, 3> vertices_1{tr_1[0], tr_1[1], tr_1[2]};
    std::array<geometry::vector_t, 3> vertices_2{tr_2[0], tr_2[1], tr_2[2]};
    std::array<int, 3> res_arr;
    for(size_t i = 0; i < 3; ++i) {
        double det = common::calc_det(vertices_1[0], vertices_1[1], vertices_1[2], vertices_2[i]);
        int sign = cmp::dbl_cmp(det, 0.0);
        if(sign > 0)
            res_arr[i] = 1;
        else if(sign < 0)
            res_arr[i] = -1;
        else
            res_arr[i] = 0;
    }
    return res_arr;
}

//one common point in 3d

//анонимный неймспэйс
bool determine_side(const geometry::vector_t &point, const geometry::vector_t &a, const geometry::vector_t &b, const geometry::vector_t &c) {
    geometry::vector_t vec_1 = cross_product(c - b, point - b);
    geometry::vector_t vec_2 = cross_product(c - b, a - b);
    return (cmp::dbl_cmp(dot_product(vec_1, vec_2), 0) >= 0);
}

bool point_in_triangle(const geometry::vector_t &point, const geometry::triangle_t &tr) {
    geometry::vector_t a = tr.vertices_[0];
    geometry::vector_t b = tr.vertices_[1];
    geometry::vector_t c = tr.vertices_[2];
    return (determine_side(point, a, b, c) && determine_side(point, b, a, c) && determine_side(point, c, a, b));
}

bool one_common_point_3D(const std::array<int, 3> res, const geometry::triangle_t &tr_1, const geometry::triangle_t &tr_2) {
    auto elem = std::find(res.begin(), res.end(), 0);
    size_t idx = std::distance(res.begin(), elem);
    geometry::vector_t point = tr_1.vertices_[idx];
    return point_in_triangle(point, tr_2); 
}
//----------------

//-----------------------------------------------------//
//------------------ 3D INTERSECTION ------------------//
//---------------------------------------------------- //

bool intersection(geometry::triangle_t tr_1, geometry::triangle_t tr_2) {
    std::array<int, 3> res_1 = check_relative_pos(tr_2, tr_1);
    int sum_1 = std::accumulate(res_1.begin(), res_1.end(), 0);

    std::array<int, 3> res_2 = check_relative_pos(tr_1, tr_2);
    int sum_2 = std::accumulate(res_2.begin(), res_2.end(), 0);

    //std::cout << "sum_1: " << sum_1 << " sum 2: " << sum_2 << std::endl;

    if(std::abs(sum_1) == 3 || std::abs(sum_2) == 3) {
        std::cout << "No intersection possible!" << std::endl;
        return false;
    }
    if(sum_1 == 0 && sum_2 == 0) {
        std::cout << "We have 2D intersection!" << std::endl;
        return intersection2D(tr_1, tr_2);
    }

    if((std::abs(sum_1) == 2 || std::abs(sum_2) == 2)) {
        if(std::abs(sum_1) == 2)
            return one_common_point_3D(res_1, tr_1, tr_2);
        return one_common_point_3D(res_2, tr_2, tr_1);
    }
    sort_triangles(tr_1, tr_2, res_1, sum_1);
    sort_triangles(tr_2, tr_1, res_2, sum_2);

    std::array<geometry::vector_t, 3> vertices_1{tr_1[0], tr_1[1], tr_1[2]};
    std::array<geometry::vector_t, 3> vertices_2{tr_2[0], tr_2[1], tr_2[2]};

    if(cmp::dbl_cmp(common::calc_det(vertices_1[0], vertices_1[1], vertices_2[1], vertices_2[0]), 0.0) >= 0 
        && cmp::dbl_cmp(common::calc_det(vertices_1[0], vertices_1[2], vertices_2[2], vertices_2[0]), 0.0) <= 0)
            return true;
    return false;
}

void sort_triangles(geometry::triangle_t &tr_1, geometry::triangle_t &tr_2, const std::array<int, 3> res_1, int sum_1) {
    tr_1.set_p(res_1, sum_1);
    int sign = (cmp::dbl_cmp(common::calc_det(tr_2[0], tr_2[1], tr_2[2], tr_1[0]), 0.0) > 0) ? 1 : -1;
    if(sign == -1)
        tr_2.swap_qr();
}

//////////////////////////////////
//for yz 
// idx_1 = 1, idx_2 = 2, idx_3 = 2, idx_4 = 1
// axe = 0 == 6 % 3

//for xz 
// idx_1 = 0, idx_2 = 2, idx_3 = 0, idx_4 = 2
// axe = 1 == 4 % 3

//for xy 
// idx_1 = 0, idx_2 = 1, idx_3 = 0, idx_4 = 1
// axe = 2 == 2 % 3
//////////////////////////////////
std::pair<geometry::triangle_t, geometry::triangle_t> projection(const geometry::triangle_t &tr_1, const geometry::triangle_t &tr_2, size_t axe_1, size_t axe_2) {
    geometry::triangle_t tmp_tr_1, tmp_tr_2;

    size_t idx_1 = axe_1;
    size_t idx_2 = axe_2;
    size_t idx_3 = (idx_1 + idx_1 * idx_1) % 3;
    size_t idx_4 = (idx_2 + idx_2 * idx_1) % 3;
    size_t axe = (idx_1 + idx_2 + idx_3 + idx_4) % 3;

    if(axe != 2) {
        //p1
        tmp_tr_1.vertices_[0].coords_[idx_1] = tr_1.vertices_[1].coords_[idx_3];
        tmp_tr_1.vertices_[0].coords_[idx_2] = tr_1.vertices_[1].coords_[idx_4];
        //q1
        tmp_tr_1.vertices_[1].coords_[idx_1] = tr_1.vertices_[0].coords_[idx_3];
        tmp_tr_1.vertices_[1].coords_[idx_2] = tr_1.vertices_[0].coords_[idx_4];
        //r1
        tmp_tr_1.vertices_[2].coords_[idx_1] = tr_1.vertices_[2].coords_[idx_3];
        tmp_tr_1.vertices_[2].coords_[idx_2] = tr_1.vertices_[2].coords_[idx_4];

        //p2
        tmp_tr_2.vertices_[0].coords_[idx_1] = tr_2.vertices_[1].coords_[idx_3];
        tmp_tr_2.vertices_[0].coords_[idx_2] = tr_2.vertices_[1].coords_[idx_4];
        //q2
        tmp_tr_2.vertices_[1].coords_[idx_1] = tr_2.vertices_[0].coords_[idx_3];
        tmp_tr_2.vertices_[1].coords_[idx_2] = tr_2.vertices_[0].coords_[idx_4];
        //r2
        tmp_tr_2.vertices_[2].coords_[idx_1] = tr_2.vertices_[2].coords_[idx_3];
        tmp_tr_2.vertices_[2].coords_[idx_2] = tr_2.vertices_[2].coords_[idx_4];
    }
    else {
        tmp_tr_1 = tr_1;
        tmp_tr_2 = tr_2;
    }
    
    tmp_tr_1.vertices_[0].coords_[axe] = 0;
    tmp_tr_1.vertices_[1].coords_[axe] = 0;
    tmp_tr_1.vertices_[2].coords_[axe] = 0;

    tmp_tr_2.vertices_[0].coords_[axe] = 0;
    tmp_tr_2.vertices_[1].coords_[axe] = 0;
    tmp_tr_2.vertices_[2].coords_[axe] = 0;

    auto prj = std::make_pair(tmp_tr_1, tmp_tr_2);
    return prj;
}

std::pair<geometry::triangle_t, geometry::triangle_t> project_coplanar(const geometry::triangle_t &tr_1, const geometry::triangle_t &tr_2) {

    //geometry::triangle_t tmp_tr_1, tmp_tr_2;

    geometry::vector_t normal = geometry::cross_product(tr_1[0] - tr_1[1], tr_1[0] - tr_1[2]);
    double n_x, n_y, n_z;

    n_x = std::abs(normal[0]);
    n_y = std::abs(normal[1]);
    n_z = std::abs(normal[2]);

    //Projection of the triangles in 3D onto 2D such that the area of the projection is maximized
    // Project onto plane YZ
    if (cmp::dbl_cmp(n_x, n_z) >= 0 && cmp::dbl_cmp(n_x, n_y) >= 0 && !normal.is_zero_vec())
        return projection(tr_1, tr_2, 1, 2);

    // Project onto plane XZ
    else if (cmp::dbl_cmp(n_y, n_z) >= 0 && cmp::dbl_cmp(n_y, n_x) >= 0 && !normal.is_zero_vec())
        return projection(tr_1, tr_2, 0, 2);

    // Project onto plane XY
    return projection(tr_1, tr_2, 0, 1);
}
//-----------------------------------------------------//
//------------------ 2D INTERSECTION ------------------//
//---------------------------------------------------- //
// --- check if p is in ++- part +--
namespace {
bool check_R1(const std::array<int, 3> res) {
    if(res[0] >= 0 && res[1] >= 0 && res[2] < 0)
        return true;
    return false;
}
bool check_R2(const std::array<int, 3> res) {
    if(res[0] >= 0 && res[1] < 0 && res[2] < 0)
        return true;
    return false;
}

//анонимный
bool determine_region(geometry::vector_t &p_1, std::array<int, 3> res, geometry::triangle_t &tr_2) {

    bool R1 = check_R1(res);
    bool R2 = check_R2(res);
    while(R1 != 1 && R2 != 1) {
        tr_2.circular_permutation();
        res = check_relative_pos(p_1, tr_2);
        R1 = check_R1(res);
        R2 = check_R2(res);   
    }
    return R1;
}

bool solution_R1(const geometry::triangle_t &tr_1, const geometry::triangle_t &tr_2){
    std::array<geometry::vector_t, 3> vrts_1{tr_1[0], tr_1[1], tr_1[2]}; // p1, q1, r1
    std::array<geometry::vector_t, 3> vrts_2{tr_2[0], tr_2[1], tr_2[2]}; // p2, q2, r2

    if(cmp::dbl_cmp(common::calc_det(vrts_2[2], vrts_2[0], vrts_1[1]), 0.0) >= 0) {
        if(cmp::dbl_cmp(common::calc_det(vrts_1[0], vrts_2[0], vrts_1[1]), 0.0) >= 0) {
            if(cmp::dbl_cmp(common::calc_det(vrts_1[0], vrts_1[1], vrts_2[2]), 0.0) >= 0) {
                return 1;
            }
        }
        else {
            if(cmp::dbl_cmp(common::calc_det(vrts_1[1], vrts_1[2], vrts_2[0]), 0.0) >= 0) {
                if(cmp::dbl_cmp(common::calc_det(vrts_1[2], vrts_1[0], vrts_2[0]), 0.0) >= 0) {
                    return 1;
                }
            }
        }
    }
    else {
        if(cmp::dbl_cmp(common::calc_det(vrts_2[2], vrts_2[0], vrts_1[2]), 0.0) >= 0) {
            if(cmp::dbl_cmp(common::calc_det(vrts_1[0], vrts_2[0], vrts_1[2]), 0.0) >= 0) {
                if(cmp::dbl_cmp(common::calc_det(vrts_1[0], vrts_1[2], vrts_2[2]), 0.0) >= 0) {
                    return 1;
                }
                if(cmp::dbl_cmp(common::calc_det(vrts_1[1], vrts_1[2], vrts_2[2]), 0.0) >= 0) {
                    return 1;
                }
            }
        }
    }
    return 0;    
}

bool solution_R2(const geometry::triangle_t &tr_1, const geometry::triangle_t &tr_2){
    std::array<geometry::vector_t, 3> vrts_1{tr_1[0], tr_1[1], tr_1[2]}; // p1, q1, r1
    std::array<geometry::vector_t, 3> vrts_2{tr_2[0], tr_2[1], tr_2[2]}; // p2, q2, r2

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
}

bool intersection2D(geometry::triangle_t tr_1, geometry::triangle_t tr_2) {
    tr_1.counter_clock();
    tr_2.counter_clock();

    auto projections = project_coplanar(tr_1, tr_2);

    geometry::triangle_t pr_tr_1 = projections.first;
    geometry::triangle_t pr_tr_2 = projections.second;
    
    geometry::vector_t p_1 = pr_tr_1[0];
    std::array<int, 3> res = check_relative_pos(p_1, pr_tr_2);

    if(std::count(res.begin(), res.end(), 0) == 3) {
        geometry::swap(pr_tr_1, pr_tr_2);
        p_1 = pr_tr_1[0];
        res = check_relative_pos(p_1, pr_tr_2);
    }
    if(std::count(res.begin(), res.end(), 0) == 3) {
        std::cout << "Two degenerates intersection" << std::endl;
        return intersection_degenerate(pr_tr_1, pr_tr_2);
    }

    if(intersec_first_step2D(res))
        return true;

    //other cases - moving p_1 to ++- or to +-- part with circular permutation of T2
    // + means det >= 0; - means det < 0;
    // [p1, p2, q2]
    // [p1, q2, r2]
    // [p1, r2, p2]

    if(determine_region(p_1, res, pr_tr_2)) {
        std::cout << "We go to R1! - edge intersection" << std::endl;
        return solution_R1(pr_tr_1, pr_tr_2);
    }
    else {
        std::cout << "We go to R2! - vertex intersection" << std::endl;
        return solution_R2(pr_tr_1, pr_tr_2);
    }

    return false;
}

std::array<int, 3> check_relative_pos(const geometry::vector_t &p_1, const geometry::triangle_t &tr_2) {
    std::array<geometry::vector_t, 3> vertices_2{tr_2[0], tr_2[1], tr_2[2]};
    std::array<int, 3> res_arr;

    for(size_t i = 0; i < 3; ++i) {
        double det = common::calc_det(p_1, vertices_2[i], vertices_2[(i + 1) % 3]);
        double res_cmp = cmp::dbl_cmp(det, 0);
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
//анонимный
bool intersec_first_step2D(const std::array<int, 3> res) {
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
    return false;
}

//const??
bool intersection_degenerate(geometry::triangle_t tr_1, geometry::triangle_t tr_2) {
    tr_1.line_counter_clock();
    tr_2.line_counter_clock();

    geometry::vector_t p1 = tr_1.vertices_[0];
    geometry::vector_t r1 = tr_1.vertices_[2];
    geometry::vector_t p2 = tr_2.vertices_[0];
    geometry::vector_t r2 = tr_2.vertices_[2];

    double det_1 = common::calc_det(p1, p2, r1);
    double det_2 = common::calc_det(p1, r2, r1);
    double det_3 = common::calc_det(p2, p1, r2);
    double det_4 = common::calc_det(p2, r1, r2);

    if(det_signs_comp(det_1, det_2) || det_signs_comp(det_3, det_4))
        return false;
    if(cmp::dbl_cmp(det_1, 0.0) == 0 && cmp::dbl_cmp(det_2, 0.0) == 0
    && cmp::dbl_cmp(det_3, 0.0) == 0 && cmp::dbl_cmp(det_4, 0.0) == 0) {
        std::cout << "Line degenerates" << std::endl;
        return one_line_degenerates(p1, r1, p2, r2);
    }
    return true;
}

bool det_signs_comp(double det_1, double det_2) {
    if((cmp::dbl_cmp(det_1, 0.0) > 0 && cmp::dbl_cmp(det_2, 0.0) > 0) || (cmp::dbl_cmp(det_1, 0.0) < 0 && cmp::dbl_cmp(det_2, 0.0) < 0))
        return true;
    return false;
}

bool one_line_degenerates(const geometry::vector_t &p1, const geometry::vector_t &r1, const geometry::vector_t &p2, const geometry::vector_t &r2) {
    double p1r1 = geometry::length(p1, r1);
    double p2r1 = geometry::length(p2, r1);
    double p1r2 = geometry::length(p1, r2);
    double p1p2 = geometry::length(p1, p2);
    double r1r2 = geometry::length(r1, r2);
    double p2r2 = geometry::length(p2, r2);

    if((cmp::dbl_cmp(p2r1 + p1p2, p1r1) == 0) ||
        (cmp::dbl_cmp(r1r2 + p1r2, p1r1) == 0) ||
        (cmp::dbl_cmp(p1p2 + p1r2, p2r2) == 0) ||
        (cmp::dbl_cmp(r1r2 + p2r1, p2r2) == 0))
        return true;
    return false;
}

} //namespace intersection