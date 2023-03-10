#include <gtest/gtest.h>
#include <fstream>
#include "matrix.hpp"

const double ACCURACY = 1E-4;

template <typename ArrT, typename T>
matrix::SquareMatrix<ArrT, T> inputMatrix (const char *filename)
{
    std::ifstream ftest(filename, std::ios::in);
    if (!ftest.is_open())
        perror("File open error:");

    size_t size;
    ftest >> size;

    matrix::SquareMatrix<ArrT, T> matr(size);

    ftest >> matr;
    std::cerr << matr;
    ftest.close();

    return matr;
}

TEST(test_matrix_ctors, copy) {
    matrix::SquareMatrix<containers::Linear<double>, double> matrix = inputMatrix<containers::Linear<double>, double>(TEST_PATH"/contest_tests/test_1.txt");
    matrix::SquareMatrix<containers::Linear<double>, double> test_matrix{matrix};
    EXPECT_EQ(matrix, test_matrix);
}

TEST(test_matrix_ctors, copy_2) {
    matrix::SquareMatrix<containers::Jagged<double>, double> matrix = inputMatrix<containers::Jagged<double>, double>(TEST_PATH"/contest_tests/test_1.txt");
    matrix::SquareMatrix<containers::Jagged<double>, double> test_matrix{matrix};
    EXPECT_EQ(matrix, test_matrix);
}

TEST(test_matrix_ctors, move) {
    matrix::SquareMatrix<containers::Linear<double>, double> matrix = inputMatrix<containers::Linear<double>, double>(TEST_PATH"/contest_tests/test_1.txt");
    matrix::SquareMatrix<containers::Linear<double>, double> tmp_matrix{matrix};
    matrix::SquareMatrix<containers::Linear<double>, double> test_matrix{std::move(tmp_matrix)};
    EXPECT_EQ(matrix, test_matrix);
}

TEST(test_matrix_ctors, move_2) {
    matrix::SquareMatrix<containers::Jagged<double>, double> matrix = inputMatrix<containers::Jagged<double>, double>(TEST_PATH"/contest_tests/test_1.txt");
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
    matrix::SquareMatrix<containers::Jagged<int>, int> matrix = inputMatrix<containers::Jagged<double>, double>(TEST_PATH"/contest_tests/test_1.txt");
    matrix::SquareMatrix<containers::Linear<double>, double> matrix_2 = inputMatrix<containers::Linear<double>, double>(TEST_PATH"/contest_tests/test_1.txt");
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
    matrix::SquareMatrix<containers::Linear<double>, double> matrix = inputMatrix<containers::Linear<double>, double>(TEST_PATH"/contest_tests/test_1.txt");
    matrix::SquareMatrix<containers::Linear<double>, double> test_matrix{0};

    test_matrix = matrix;

    EXPECT_EQ(matrix, test_matrix);
}

TEST(test_matrix_ctors, copy_assign_2) {
    matrix::SquareMatrix<containers::Jagged<double>, double> matrix = inputMatrix<containers::Jagged<double>, double>(TEST_PATH"/contest_tests/test_1.txt");
    matrix::SquareMatrix<containers::Jagged<double>, double> test_matrix{5};

    test_matrix = matrix;

    EXPECT_EQ(matrix, test_matrix);
}

TEST(test_matrix_ctors, move_assign) {
    matrix::SquareMatrix<containers::Linear<double>, double> matrix = inputMatrix<containers::Linear<double>, double>(TEST_PATH"/contest_tests/test_1.txt");
    matrix::SquareMatrix<containers::Linear<double>, double> tmp_matrix{matrix};
    matrix::SquareMatrix<containers::Linear<double>, double> test_matrix{0};
    test_matrix = std::move(tmp_matrix);

    EXPECT_EQ(matrix, test_matrix);
}

TEST(test_matrix_ctors, move_assign_2) {
    matrix::SquareMatrix<containers::Jagged<double>, double> matrix = inputMatrix<containers::Jagged<double>, double>(TEST_PATH"/contest_tests/test_1.txt");
    matrix::SquareMatrix<containers::Jagged<double>, double> tmp_matrix{matrix};
    matrix::SquareMatrix<containers::Jagged<double>, double> test_matrix{5};
    test_matrix = std::move(tmp_matrix);

    EXPECT_EQ(matrix, test_matrix);
}