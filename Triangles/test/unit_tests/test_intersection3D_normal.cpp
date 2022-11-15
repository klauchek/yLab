#include <gtest/gtest.h>
#include "intersection.hpp"

TEST(test_3D, parallel) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{0, 4, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{0, 0, 3};
    struct geometry::vector_t vec21{-4.01, 9.65, 3};
    struct geometry::vector_t vec22{3.79, 2.56, 3};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_FALSE(res_intersec);
}

TEST(test_3D, close_parallel_true) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-3, 0, 0};
    struct geometry::vector_t vec12{0, 2, 0};
    //2 tr
    struct geometry::vector_t vec20{-3.18, 4.4, 0.00001};
    struct geometry::vector_t vec21{-2.23, 0.89, 0.00001};
    struct geometry::vector_t vec22{6.16, 2.16, 0.00001};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_FALSE(res_intersec); //enough accuracy
}

TEST(test_3D, close_parallel_false) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-3, 0, 0};
    struct geometry::vector_t vec12{0, 2, 0};
    //2 tr
    struct geometry::vector_t vec20{-3.18, 4.4, 0.0000001};
    struct geometry::vector_t vec21{-2.23, 0.89, 0.0000001};
    struct geometry::vector_t vec22{6.16, 2.16, 0.0000001};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);//not enough accuracy
}

// TEST(test_3D, close_without_intersec) {
//     //1 tr
//     struct geometry::vector_t vec10{1.1, 0, 0};
//     struct geometry::vector_t vec11{1.5, 1, 0};
//     struct geometry::vector_t vec12{-1, 0, 0};
//     //2 tr
//     struct geometry::vector_t vec20{0.1, 0.4, 0};
//     struct geometry::vector_t vec21{0.1, 0.4, 0};
//     struct geometry::vector_t vec22{1.1, 0, 1};

//     geometry::triangle_t triangle_1(vec10, vec11, vec12);
//     geometry::triangle_t triangle_2(vec20, vec21, vec22);

//     bool res_intersec = intersection::intersection(triangle_1, triangle_2);
//     EXPECT_TRUE(res_intersec);
// }

// TEST(test_3D, without_intersec) {
//     //1 tr
//     struct geometry::vector_t vec10{1.1, 0, 0};
//     struct geometry::vector_t vec11{1.5, 1, 0};
//     struct geometry::vector_t vec12{-1, 0, 0};
//     //2 tr
//     struct geometry::vector_t vec20{0.1, 0.4, 0};
//     struct geometry::vector_t vec21{0.1, 0.4, 0};
//     struct geometry::vector_t vec22{1.1, 0, 1};

//     geometry::triangle_t triangle_1(vec10, vec11, vec12);
//     geometry::triangle_t triangle_2(vec20, vec21, vec22);

//     bool res_intersec = intersection::intersection(triangle_1, triangle_2);
//     EXPECT_TRUE(res_intersec);
// }

// TEST(test_3D, simple) {
//     //1 tr
//     struct geometry::vector_t vec10{1.1, 0, 0};
//     struct geometry::vector_t vec11{1.5, 1, 0};
//     struct geometry::vector_t vec12{-1, 0, 0};
//     //2 tr
//     struct geometry::vector_t vec20{0.1, 0.4, 0};
//     struct geometry::vector_t vec21{0.1, 0.4, 0};
//     struct geometry::vector_t vec22{1.1, 0, 1};

//     geometry::triangle_t triangle_1(vec10, vec11, vec12);
//     geometry::triangle_t triangle_2(vec20, vec21, vec22);

//     bool res_intersec = intersection::intersection(triangle_1, triangle_2);
//     EXPECT_TRUE(res_intersec);
// }

// TEST(test_3D, vertex_in_tr) {
//     //1 tr
//     struct geometry::vector_t vec10{1.1, 0, 0};
//     struct geometry::vector_t vec11{1.5, 1, 0};
//     struct geometry::vector_t vec12{-1, 0, 0};
//     //2 tr
//     struct geometry::vector_t vec20{0.1, 0.4, 0};
//     struct geometry::vector_t vec21{0.1, 0.4, 0};
//     struct geometry::vector_t vec22{1.1, 0, 1};

//     geometry::triangle_t triangle_1(vec10, vec11, vec12);
//     geometry::triangle_t triangle_2(vec20, vec21, vec22);

//     bool res_intersec = intersection::intersection(triangle_1, triangle_2);
//     EXPECT_TRUE(res_intersec);
// }

// TEST(test_3D, edge_in_tr) {
//     //1 tr
//     struct geometry::vector_t vec10{1.1, 0, 0};
//     struct geometry::vector_t vec11{1.5, 1, 0};
//     struct geometry::vector_t vec12{-1, 0, 0};
//     //2 tr
//     struct geometry::vector_t vec20{0.1, 0.4, 0};
//     struct geometry::vector_t vec21{0.1, 0.4, 0};
//     struct geometry::vector_t vec22{1.1, 0, 1};

//     geometry::triangle_t triangle_1(vec10, vec11, vec12);
//     geometry::triangle_t triangle_2(vec20, vec21, vec22);

//     bool res_intersec = intersection::intersection(triangle_1, triangle_2);
//     EXPECT_TRUE(res_intersec);
// }

// TEST(test_3D, edges_angle) {
//     //1 tr
//     struct geometry::vector_t vec10{1.1, 0, 0};
//     struct geometry::vector_t vec11{1.5, 1, 0};
//     struct geometry::vector_t vec12{-1, 0, 0};
//     //2 tr
//     struct geometry::vector_t vec20{0.1, 0.4, 0};
//     struct geometry::vector_t vec21{0.1, 0.4, 0};
//     struct geometry::vector_t vec22{1.1, 0, 1};

//     geometry::triangle_t triangle_1(vec10, vec11, vec12);
//     geometry::triangle_t triangle_2(vec20, vec21, vec22);

//     bool res_intersec = intersection::intersection(triangle_1, triangle_2);
//     EXPECT_TRUE(res_intersec);
// }

// TEST(test_3D, vertices_angle) {
//     //1 tr
//     struct geometry::vector_t vec10{1.1, 0, 0};
//     struct geometry::vector_t vec11{1.5, 1, 0};
//     struct geometry::vector_t vec12{-1, 0, 0};
//     //2 tr
//     struct geometry::vector_t vec20{0.1, 0.4, 0};
//     struct geometry::vector_t vec21{0.1, 0.4, 0};
//     struct geometry::vector_t vec22{1.1, 0, 1};

//     geometry::triangle_t triangle_1(vec10, vec11, vec12);
//     geometry::triangle_t triangle_2(vec20, vec21, vec22);

//     bool res_intersec = intersection::intersection(triangle_1, triangle_2);
//     EXPECT_TRUE(res_intersec);
// }

// TEST(test_3D, vertex_on_edge) {
//     //1 tr
//     struct geometry::vector_t vec10{1.1, 0, 0};
//     struct geometry::vector_t vec11{1.5, 1, 0};
//     struct geometry::vector_t vec12{-1, 0, 0};
//     //2 tr
//     struct geometry::vector_t vec20{0.1, 0.4, 0};
//     struct geometry::vector_t vec21{0.1, 0.4, 0};
//     struct geometry::vector_t vec22{1.1, 0, 1};

//     geometry::triangle_t triangle_1(vec10, vec11, vec12);
//     geometry::triangle_t triangle_2(vec20, vec21, vec22);

//     bool res_intersec = intersection::intersection(triangle_1, triangle_2);
//     EXPECT_TRUE(res_intersec);
// }