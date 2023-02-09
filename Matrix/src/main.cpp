#include "matrix.hpp"

int main() {
    matrix::Matrix<containers::Linear<int>> m(5);

    std::cout << "sz " << m.size() << std::endl;
}