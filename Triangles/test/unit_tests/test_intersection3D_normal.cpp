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
    res_intersec = intersection::intersection(triangle_2, triangle_1);
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
    res_intersec = intersection::intersection(triangle_2, triangle_1);
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
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);//not enough accuracy
}

//interesting case
TEST(test_3D, close_without_intersec) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-3, 0, 0};
    struct geometry::vector_t vec12{0, 2, 0};
    //2 tr
    struct geometry::vector_t vec20{-2.8, 4.4, -3};
    struct geometry::vector_t vec21{-2.19999, 0.25, -2}; //intersec in -2.2
    struct geometry::vector_t vec22{3.3, 2.5, 3};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_FALSE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_FALSE(res_intersec);
}

TEST(test_3D, without_intersec) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-3, 0, 0};
    struct geometry::vector_t vec12{0, 2, 0};
    //2 tr
    struct geometry::vector_t vec20{-2.8, 4.4, -3};
    struct geometry::vector_t vec21{1.84, 1.46, -2};
    struct geometry::vector_t vec22{3.3, 2.5, 3};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_FALSE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_FALSE(res_intersec);
}

TEST(test_3D, simple) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-3, 0, 0};
    struct geometry::vector_t vec12{0, 2, 0};
    //2 tr
    struct geometry::vector_t vec20{-2.22, 2.24, -3};
    struct geometry::vector_t vec21{2, -1, 3};
    struct geometry::vector_t vec22{-2.99, 3.42, -2};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_3D, vertex_in_tr) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-3, 0, 0};
    struct geometry::vector_t vec12{0, 2, 0};
    //2 tr
    struct geometry::vector_t vec20{-1.04, 0.74, 0};
    struct geometry::vector_t vec21{-1.22, -0.17, 2.25};
    struct geometry::vector_t vec22{1.86, 4.6, 2};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_3D, edge_in_tr) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-3, 0, 0};
    struct geometry::vector_t vec12{0, 2, 0};
    //2 tr
    struct geometry::vector_t vec20{-1.08, 1, 0};
    struct geometry::vector_t vec21{-1.27, 0.5, 0};
    struct geometry::vector_t vec22{-0.92, 0.86, 0.45};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_3D, edges_angle) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-3, 0, 0};
    struct geometry::vector_t vec12{0, 2, 0};
    //2 tr
    struct geometry::vector_t vec20{-0.85, 1.07, 1.05};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec11, vec12);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_3D, vertices_angle) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-3, 0, 0};
    struct geometry::vector_t vec12{0, 2, 0};
    //2 tr
    struct geometry::vector_t vec20{-1.57, 1.25, 0.97};
    struct geometry::vector_t vec21{0.52, 1.22, 0.87};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec12);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_3D, vertex_on_edge) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-3, 0, 0};
    struct geometry::vector_t vec12{0, 2, 0};
    //2 tr
    struct geometry::vector_t vec20{-1.27, 1.15, 0};
    struct geometry::vector_t vec21{-0.56, 1.37, 1.3};
    struct geometry::vector_t vec22{-1.63, 0.27, 1.14};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}