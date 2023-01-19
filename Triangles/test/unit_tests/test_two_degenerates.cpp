#include <gtest/gtest.h>
#include "intersection.hpp"

TEST(test_deg, segments_intersec) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{0, 2, 0};
    struct geometry::vector_t vec12{0, -0.5, 0};
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

TEST(test_deg, segments_common_point) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-0.8, 0, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{0, 0, 0};
    struct geometry::vector_t vec21{-0.48, 0.77, 0};
    struct geometry::vector_t vec22{-0.48, 0.77, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_deg, segments_common_vertex) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-0.8, 0, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{-0.8, 0, 0};
    struct geometry::vector_t vec21{-0.48, 0.78, 0};
    struct geometry::vector_t vec22{-0.48, 0.78, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
}

TEST(test_deg, segments_overlap) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-0.8, 0, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{-0.3, 0, 0};
    struct geometry::vector_t vec21{-1.41, 0, 0};
    struct geometry::vector_t vec22{-1.59, 0, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
}

TEST(test_deg, segments_parallel) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-0.8, 0, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{-0.42, 0.8, 0};
    struct geometry::vector_t vec21{-0.71, 0.8, 0};
    struct geometry::vector_t vec22{-0.01, 0.8, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_FALSE(res_intersec);
    res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_FALSE(res_intersec);
}


TEST(test_deg, segments_parallel_2) {
    //1 tr
    struct geometry::vector_t vec10{1, 1, 1};
    struct geometry::vector_t vec11{2, 2, 2};
    struct geometry::vector_t vec12{3, 3, 3};
    //2 tr
    struct geometry::vector_t vec20{1, 1, 0};
    struct geometry::vector_t vec21{2, 2, 0};
    struct geometry::vector_t vec22{3, 3, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_FALSE(res_intersec);
    res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_FALSE(res_intersec);
}

TEST(test_deg, segments_on_one_line) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-0.8, 0, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{-1.76, 0, 0};
    struct geometry::vector_t vec21{-1.14, 0, 0};
    struct geometry::vector_t vec22{-1.59, 0, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_FALSE(res_intersec);
    res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_FALSE(res_intersec);
}

TEST(test_deg, segments_vrts_on_one_line) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-0.8, 0, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{-1.31, 0.84, 0};
    struct geometry::vector_t vec21{-1.4, 0, 0};
    struct geometry::vector_t vec22{-1.36, 0, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_FALSE(res_intersec);
    res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_FALSE(res_intersec);
}


TEST(test_deg, segments_vrtx_intersec) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-0.8225, 0, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{-0.88, 0.11, 0};
    struct geometry::vector_t vec21{-0.65, -0.33, 0};
    struct geometry::vector_t vec22{-0.65, -0.33, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
}

TEST(test_deg, segment_point_without_intersec) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-0.8, 0, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{-1.4, 0, 0};
    struct geometry::vector_t vec21{-1.4, 0, 0};
    struct geometry::vector_t vec22{-1.4, 0, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_FALSE(res_intersec);
    res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_FALSE(res_intersec);
}


///failed



TEST(test_deg, segment_point_on_one_line) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-0.8, 0, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{-0.9, 0, 0};
    struct geometry::vector_t vec21{-0.9, 0, 0};
    struct geometry::vector_t vec22{-0.9, 0, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_FALSE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_FALSE(res_intersec);
}

TEST(test_deg, point_on_segment) {
    //1 tr
    struct geometry::vector_t vec10{0, 0, 0};
    struct geometry::vector_t vec11{-0.8, 0, 0};
    struct geometry::vector_t vec12{3, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{-0.68, 0, 0};
    struct geometry::vector_t vec21{-0.68, 0, 0};
    struct geometry::vector_t vec22{-0.68, 0, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
}

TEST(test_deg, point_point) {
    struct geometry::vector_t vec10{-0.9, 0, 0};
    struct geometry::vector_t vec11{-0.9, 0, 0};
    struct geometry::vector_t vec12{-0.9, 0, 0};
    //2 tr
    struct geometry::vector_t vec20{-0.9, 0, 0};
    struct geometry::vector_t vec21{-0.9, 0, 0};
    struct geometry::vector_t vec22{-0.9, 0, 0};

    geometry::triangle_t triangle_1(vec10, vec11, vec12);
    geometry::triangle_t triangle_2(vec20, vec21, vec22);

    bool res_intersec = intersection::intersection(triangle_2, triangle_1);
    EXPECT_TRUE(res_intersec);
    res_intersec = intersection::intersection(triangle_1, triangle_2);
    EXPECT_TRUE(res_intersec);
}