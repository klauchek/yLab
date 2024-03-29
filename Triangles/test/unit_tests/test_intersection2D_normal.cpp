#include <gtest/gtest.h>
#include "intersection.hpp"

TEST(test_2D, intersec_vertex_vertex) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-3, 0, 0};
    struct geometry::vector_t vec12{0, 2, 0};
    //2 tr
    struct geometry::vector_t vec20{-0.7, 0.68, 0};
    struct geometry::vector_t vec21{2.04, 2.64, 0};
    struct geometry::vector_t vec22{-0.74, 3.21, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_2D, intersec_edge_vertex) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-3, 0, 0};
    struct geometry::vector_t vec12{0, 2, 0};
    //2 tr
    struct geometry::vector_t vec20{-0.7, 0.68, 0};
    struct geometry::vector_t vec21{-0.77, 2.35, 0};
    struct geometry::vector_t vec22{-2.85, 1.4, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_2D, intersec_edge_edge) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-3, 0, 0};
    struct geometry::vector_t vec12{0, 2, 0};
    //2 tr
    struct geometry::vector_t vec20{-0.7, 0.68, 0};
    struct geometry::vector_t vec21{-0.77, 2.35, 0};
    struct geometry::vector_t vec22{-1.63, 0.54, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_2D, common_vertex) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-3, 0, 0};
    struct geometry::vector_t vec12{0, 2, 0};
    //2 tr
    struct geometry::vector_t vec20{1.38, 2.53, 0};
    struct geometry::vector_t vec21{-0.63, 2.91, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec12);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_2D, edge_on_edge) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-3, 0, 0};
    struct geometry::vector_t vec12{0, 2, 0};
    //2 tr
    struct geometry::vector_t vec20{-0.41, 1.73, 0};
    struct geometry::vector_t vec21{-2.68, 0.21, 0};
    struct geometry::vector_t vec22{-1.91, 1.89, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_2D, vertex_on_edge) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-3, 0, 0};
    struct geometry::vector_t vec12{0, 2, 0};
    //2 tr
    struct geometry::vector_t vec20{-1, 1.33, 0};
    struct geometry::vector_t vec21{-1.51, 2.31, 0};
    struct geometry::vector_t vec22{-2.21, 1.64, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_2D, no_intersec) {
    //1 tr
    struct geometry::vector_t vec10{1, 1, 1};
    struct geometry::vector_t vec11{3, 3, 3};
    struct geometry::vector_t vec12{1.4, 1.4, 2.26};
    //2 tr
    struct geometry::vector_t vec20{1, 1, 0};
    struct geometry::vector_t vec21{3, 3, 2};
    struct geometry::vector_t vec22{2.34, 2.34, 0.5};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_FALSE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_FALSE(res_intersec);
}

TEST(test_2D, intersec) {
    //1 tr
    struct geometry::vector_t vec10{1, 1, -0.57};
    struct geometry::vector_t vec11{3, 3, 3};
    struct geometry::vector_t vec12{1.4, 1.4, 2.26};
    //2 tr
    struct geometry::vector_t vec20{1, 1, 0};
    struct geometry::vector_t vec21{3, 3, 2};
    struct geometry::vector_t vec22{2.34, 2.34, 0.5};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}
