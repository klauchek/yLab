#include <gtest/gtest.h>
#include <fstream>
#include "matrix.hpp"

template <typename ArrT, typename T>
matrix::SquareMatrix<ArrT, T> inputMatrix(const char *filename)
{
    std::ifstream ftest(filename, std::ios::in);
    if (!ftest.is_open())
        perror("File open error:");

    size_t size;
    ftest >> size;

    matrix::SquareMatrix<ArrT, T> matr(size);

    ftest >> matr;
    ftest.close();

    return matr;
}

//------------------------------------------------------------------------//
//-------------------- MATRIX CONSTRUCTORS TESTING -----------------------//
//------------------------------------------------------------------------//

TEST(test_matrix_ctors, copy) {
    matrix::SquareMatrix<containers::Linear<double>, double> matrix = inputMatrix<containers::Linear<double>, double>(TEST_PATH"/my_tests/test_1.txt");
    matrix::SquareMatrix<containers::Linear<double>, double> test_matrix{matrix};
    EXPECT_EQ(matrix, test_matrix);
}

TEST(test_matrix_ctors, copy_2) {
    matrix::SquareMatrix<containers::Jagged<double>, double> matrix = inputMatrix<containers::Jagged<double>, double>(TEST_PATH"/my_tests/test_1.txt");
    matrix::SquareMatrix<containers::Jagged<double>, double> test_matrix{matrix};
    EXPECT_EQ(matrix, test_matrix);
}

TEST(test_matrix_ctors, move) {
    matrix::SquareMatrix<containers::Linear<double>, double> matrix = inputMatrix<containers::Linear<double>, double>(TEST_PATH"/my_tests/test_1.txt");
    matrix::SquareMatrix<containers::Linear<double>, double> tmp_matrix{matrix};
    matrix::SquareMatrix<containers::Linear<double>, double> test_matrix{std::move(tmp_matrix)};
    EXPECT_EQ(matrix, test_matrix);
}

TEST(test_matrix_ctors, move_2) {
    matrix::SquareMatrix<containers::Jagged<double>, double> matrix = inputMatrix<containers::Jagged<double>, double>(TEST_PATH"/my_tests/test_1.txt");
    matrix::SquareMatrix<containers::Jagged<double>, double> tmp_matrix{matrix};
    matrix::SquareMatrix<containers::Jagged<double>, double> test_matrix{std::move(tmp_matrix)};
    EXPECT_EQ(matrix, test_matrix);
}

TEST(test_matrix_ctors, coercion) {
    matrix::SquareMatrix<containers::Jagged<double>, double> matrix = inputMatrix<containers::Jagged<double>, double>(TEST_PATH"/contest_tests/test_12.txt");
    matrix::SquareMatrix<containers::Linear<double>, double> matrix_2 = inputMatrix<containers::Linear<double>, double>(TEST_PATH"/contest_tests/test_12.txt");
    matrix::SquareMatrix<containers::Linear<double>, double> test_matrix{matrix};
    EXPECT_EQ(matrix_2, test_matrix);
}

TEST(test_matrix_ctors, coercion_2) {
    matrix::SquareMatrix<containers::Jagged<int>, int> matrix = inputMatrix<containers::Jagged<double>, double>(TEST_PATH"/my_tests/test_1.txt");
    matrix::SquareMatrix<containers::Linear<double>, double> matrix_2 = inputMatrix<containers::Linear<double>, double>(TEST_PATH"/my_tests/test_1.txt");
    matrix::SquareMatrix<containers::Linear<double>, double> test_matrix{matrix};
    EXPECT_EQ(matrix_2, test_matrix);
}

TEST(test_matrix_ctors, coercion_3) {
    matrix::SquareMatrix<containers::Linear<double>, double> matrix = inputMatrix<containers::Linear<double>, double>(TEST_PATH"/contest_tests/test_12.txt");
    matrix::SquareMatrix<containers::Jagged<double>, double> matrix_2 = inputMatrix<containers::Jagged<double>, double>(TEST_PATH"/contest_tests/test_12.txt");
    matrix::SquareMatrix<containers::Jagged<double>, double> test_matrix{matrix};
    EXPECT_EQ(matrix_2, test_matrix);
}

TEST(test_matrix_ctors, copy_assign) {
    matrix::SquareMatrix<containers::Linear<double>, double> matrix = inputMatrix<containers::Linear<double>, double>(TEST_PATH"/my_tests/test_1.txt");
    matrix::SquareMatrix<containers::Linear<double>, double> test_matrix{0};

    test_matrix = matrix;

    EXPECT_EQ(matrix, test_matrix);
}

TEST(test_matrix_ctors, copy_assign_2) {
    matrix::SquareMatrix<containers::Jagged<double>, double> matrix = inputMatrix<containers::Jagged<double>, double>(TEST_PATH"/my_tests/test_1.txt");
    matrix::SquareMatrix<containers::Jagged<double>, double> test_matrix{5};

    test_matrix = matrix;

    EXPECT_EQ(matrix, test_matrix);
}

TEST(test_matrix_ctors, move_assign) {
    matrix::SquareMatrix<containers::Linear<double>, double> matrix = inputMatrix<containers::Linear<double>, double>(TEST_PATH"/my_tests/test_1.txt");
    matrix::SquareMatrix<containers::Linear<double>, double> tmp_matrix{matrix};
    matrix::SquareMatrix<containers::Linear<double>, double> test_matrix{0};
    test_matrix = std::move(tmp_matrix);

    EXPECT_EQ(matrix, test_matrix);
}

TEST(test_matrix_ctors, move_assign_2) {
    matrix::SquareMatrix<containers::Jagged<double>, double> matrix = inputMatrix<containers::Jagged<double>, double>(TEST_PATH"/my_tests/test_1.txt");
    matrix::SquareMatrix<containers::Jagged<double>, double> tmp_matrix{matrix};
    matrix::SquareMatrix<containers::Jagged<double>, double> test_matrix{0};
    test_matrix = std::move(tmp_matrix);

    EXPECT_EQ(matrix, test_matrix);
}

TEST(test_matrix_ctors, from_iterators_1) {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix::SquareMatrix<containers::Jagged<int>, int> matrix(3, v.begin(), v.end());
    matrix::SquareMatrix<containers::Jagged<int>, int> matrix_2 = inputMatrix<containers::Jagged<int>, int>(TEST_PATH"/my_tests/from_iters1.txt");

    EXPECT_EQ(matrix, matrix_2);
}

TEST(test_matrix_ctors, from_iterators_2) {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
    matrix::SquareMatrix<containers::Linear<int>, int> matrix(5, v.begin(), v.end());
    matrix::SquareMatrix<containers::Linear<int>, int> matrix_2 = inputMatrix<containers::Linear<int>, int>(TEST_PATH"/my_tests/from_iters2.txt");

    EXPECT_EQ(matrix, matrix_2);
}

TEST(test_matrix_ctors, eye_1) {
    matrix::SquareMatrix<containers::Linear<int>, int> matrix{5};
    matrix = matrix::SquareMatrix<containers::Linear<int>, int>::eye(5);
    matrix::SquareMatrix<containers::Linear<int>, int> matrix_2 = inputMatrix<containers::Linear<int>, int>(TEST_PATH"/my_tests/eye.txt");

    EXPECT_EQ(matrix, matrix_2);
}

TEST(test_matrix_ctors, eye_2) {
    matrix::SquareMatrix<containers::Jagged<int>, int> matrix{5};
    matrix = matrix::SquareMatrix<containers::Jagged<int>, int>::eye(5);
    matrix::SquareMatrix<containers::Jagged<int>, int> matrix_2 = inputMatrix<containers::Jagged<int>, int>(TEST_PATH"/my_tests/eye.txt");

    EXPECT_EQ(matrix, matrix_2);
}

//------------------------------------------------------------------------//
//-------------------- DETERMINANT CALCULATION TESTING -------------------//
//------------------------------------------------------------------------//

const double ACCURACY = 1E-4;
template <typename T>
void test_det(const char *filename_test, const char *filename_ans)
{
    matrix::SquareMatrix<containers::Linear<double>, double> matrix_lin = inputMatrix<containers::Linear<double>, double>(filename_test);
    matrix::SquareMatrix<containers::Jagged<double>, double> matrix_jag = inputMatrix<containers::Jagged<double>, double>(filename_test);

    std::ifstream ftest(filename_ans, std::ios::in);
    if (!ftest.is_open())
        perror("File open error:");

    T right_ans;
    ftest >> right_ans;
    ftest.close();

    T ans_lin = right_ans - matrix_lin.calc_det();
    T ans_jag = right_ans - matrix_jag.calc_det();

    std::cerr << "ans lin " << ans_lin << std::endl;
    std::cerr << "ans jag " << ans_jag << std::endl;

    EXPECT_EQ(std::abs(ans_lin) < ACCURACY, true);
    EXPECT_EQ(std::abs(ans_jag) < ACCURACY, true);
}

TEST(test_determinant, sz_5_int) {
    test_det<double>(TEST_PATH"/my_tests/test_1.txt", TEST_PATH"/my_tests/answers/ans_1.txt");
}

TEST(test_determinant, sz_30_0) {
    test_det<double>(TEST_PATH"/my_tests/test_2.txt", TEST_PATH"/my_tests/answers/ans_2.txt");
}

TEST(test_determinant, sz_100_eye) {
    test_det<double>(TEST_PATH"/my_tests/test_3.txt", TEST_PATH"/my_tests/answers/ans_3.txt");
}

TEST(test_determinant, sz_8_int) {
    test_det<double>(TEST_PATH"/my_tests/test_4.txt", TEST_PATH"/my_tests/answers/ans_4.txt");
}

TEST(test_determinant, sz_100_int) {
    test_det<double>(TEST_PATH"/my_tests/test_5.txt", TEST_PATH"/my_tests/answers/ans_5.txt");
}

TEST(test_determinant, sz_5_double) {
    test_det<double>(TEST_PATH"/my_tests/test_6.txt", TEST_PATH"/my_tests/answers/ans_6.txt");
}