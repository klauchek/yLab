#include <gtest/gtest.h>
#include "intersection.hpp"

TEST(test_3D_deg, seg_triag_without_intersec_3D) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{0, 2, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{1, 1, 1};
    struct geometry::vector_t vec21{1, 1, 3};
    struct geometry::vector_t vec22{1, 1, 3};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_FALSE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_FALSE(res_intersec);
}

TEST(test_3D_deg, seg_triag_intersec_3D) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{0, 2, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{0.72, 1.48, -1};
    struct geometry::vector_t vec21{1, 1, 3};
    struct geometry::vector_t vec22{1, 1, 3};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_3D_deg, seg_one_point_in_triag_3D) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{0, 2, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{0.42, 0.98, 0};
    struct geometry::vector_t vec21{1, 1, 3};
    struct geometry::vector_t vec22{1, 1, 3};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_2D_deg, seg_triag_without_intersec_2D) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{0, 2, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{-0.82, 0.23, 0};
    struct geometry::vector_t vec21{-0.48, 1.14, 0};
    struct geometry::vector_t vec22{-0.48, 1.14, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_FALSE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_FALSE(res_intersec);
}

TEST(test_2D_deg, seg_triag_without_intersec_2D_2) {
    //the segment lies on the extension of the edge of the triangle
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{0, 2, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{-0.38, 0, 0};
    struct geometry::vector_t vec21{-0.86, 0, 0};
    struct geometry::vector_t vec22{-0.86, 0, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_FALSE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_FALSE(res_intersec);
}

TEST(test_2D_deg, seg_triag_without_intersec_2D_3) {
    //the segment lies on the extension of the edge of the triangle
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{0, 2, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{3.89, 0, 0};
    struct geometry::vector_t vec21{3.41, 0, 0};
    struct geometry::vector_t vec22{3.41, 0, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_FALSE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_FALSE(res_intersec);
}

TEST(test_2D_deg, seg_triag_without_intersec_2D_4) {
    //the segment lies on the extension of the edge of the triangle
    //1 tr
    struct geometry::vector_t vec10{-5.12, 2.37, -4.74};
    struct geometry::vector_t vec11{-2.75, 1.29, 0};
    struct geometry::vector_t vec12{-5.32, 1.11, 0};
    //2 tr
    struct geometry::vector_t vec20{1.2, 1.84, -1};
    struct geometry::vector_t vec21{1.55, 1.6, 0};
    struct geometry::vector_t vec22{1.55, 1.6, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_FALSE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_FALSE(res_intersec);
}

TEST(test_2D_deg, seg_triag_edge_intersec_2D) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{0, 2, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{0.82, 0.78, 0};
    struct geometry::vector_t vec21{2.41, 2.2, 0};
    struct geometry::vector_t vec22{2.41, 2.2, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_2D_deg, seg_triag_vertex_intersec_2D) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{0, 2, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{-0.44, -0.44, 0};
    struct geometry::vector_t vec21{0.52, 0.52, 0};
    struct geometry::vector_t vec22{0.52, 0.52, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_2D_deg, seg_in_triag_2D) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{0, 2, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{0.42, 0.98, 0};
    struct geometry::vector_t vec21{1, 1, 0};
    struct geometry::vector_t vec22{1, 1, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_2D_deg, seg_triag_common_edge_2D) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{0, 2, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{0, -0.5, 0};
    struct geometry::vector_t vec21{0, 1, 0};
    struct geometry::vector_t vec22{0, 1.6, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_2D_deg, seg_triag_common_point_2D) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{0, 2, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{-0.45, 0.18, 0};
    struct geometry::vector_t vec21{-0.45, 0.18, 0};
    struct geometry::vector_t vec22{0, 1.6, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_2D_deg, seg_triag_common_vertex_2D) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{0, 2, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    //2 tr
    struct geometry::vector_t vec20{-0.45, 0.18, 0};
    struct geometry::vector_t vec21{-0.45, 0.18, 0};
    struct geometry::vector_t vec22{0, 0, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_2D_deg, vertex_on_seg_2D) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{0, 2, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{-0.25, 0.25, 0};
    struct geometry::vector_t vec21{-0.25, 0.25, 0};
    struct geometry::vector_t vec22{0.25, -0.25, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}


TEST(test_2D_deg, point_in_triag) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{0, 2, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{0.46, 0.55, 0};
    struct geometry::vector_t vec21{0.46, 0.55, 0};
    struct geometry::vector_t vec22{0.46, 0.55, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec); 
}

TEST(test_2D_deg, point_not_in_triag) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{0, 2, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{-0.46, 0.77, 0};
    struct geometry::vector_t vec21{-0.46, 0.77, 0};
    struct geometry::vector_t vec22{-0.46, 0.77, 0};
    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_FALSE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_FALSE(res_intersec);
}
