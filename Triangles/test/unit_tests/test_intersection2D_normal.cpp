// #include <gtest/gtest.h>
// #include "intersection.hpp"

// TEST(test_2D, simple) {
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