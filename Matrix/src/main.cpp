#include "matrix.hpp"
#include <vector>

int main() {

    size_t n;
	std::cin >> n;

    matrix::SquareMatrix<containers::Linear<double>, double> matrix(n);
    std::cin >> matrix;

    std::cout << matrix.calc_det() << std::endl;

}