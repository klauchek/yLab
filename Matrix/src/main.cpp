#include "matrix.hpp"
#include <vector>

int main() {

    size_t n;
	std::cin >> n;

    matrix::SquareMatrix<containers::Linear<double>, double> matrix(n);
    std::cin >> matrix;

    matrix::SquareMatrix<containers::Linear<double>, double> m1(n);
    matrix::SquareMatrix<containers::Linear<double>, double> m2(n);
    if(m1.equal(m2) && m1 == m2)
        std::cout << "they are equal! " << std::endl;

    matrix::SquareMatrix<containers::Jagged<double>, double> m3(n);
    matrix::SquareMatrix<containers::Jagged<double>, double> m4(n);
    if(m3.equal(m4) && m3 == m4)
        std::cout << "they are equal jag! " << std::endl;
    // for(int i = 0; i < n; ++i){
    //     for(int j = 0; j < n; ++j)
    //         std::cout << matrix[i][j];
    //     std::cout << std::endl;
    // }

    // std::cout << std::endl;
    // std::cout << "DET: " << matrix.calc_det() << std::endl;
    // std::cout << std::endl;

    matrix::SquareMatrix<containers::Linear<int>, int> m_lin(3, 1);
    std::cout << std::endl;
    std::cout << "LINEAR COPY CTOR" << std::endl;
    std::cout << std::endl;

    matrix::SquareMatrix<containers::Jagged<int>, int> m_jag(5, 3);
    matrix::SquareMatrix<containers::Linear<int>, int> m_lin_2 = m_jag;
    
    //m_lin = m_lin_2;

    //propable for this we need cohersion ctor
    //m_lin(m_lin_2);

    //std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9};
    //matrix::SquareMatrix<containers::Linear<int>, int> m_lin(3, vec.begin(), vec.end());
    //matrix::SquareMatrix<containers::Linear<int>, int> m_lin_2(5, 2);
    //matrix::SquareMatrix<containers::Jagged<int>, int> m_jag(3, vec.begin(), vec.end());
    
    //m_lin.swap_rows(0, 1);
    //m_lin.swap_columns(1, 2);

    // for(int i = 0; i < 3; ++i){
    //     for(int j = 0; j < 3; ++j)
    //         std::cout << m_lin[i][j];
    //     std::cout << std::endl;
    // }

    std::cout << std::endl;


    matrix = matrix::SquareMatrix<containers::Linear<double>, double>::eye(5);


    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j)
            std::cout << matrix[i][j];
        std::cout << std::endl;
    }

    // for(int i = 0; i < 5; ++i) {
    //     for(int j = 0; j < 5; ++j)
    //         std::cout << m[i][j];
    //     std::cout << std::endl;
    // }
    // for(int i = 0; i < 3; ++i){
    //     for(int j = 0; j < 3; ++j)
    //         std::cout << m_jag[i][j];
    //     std::cout << std::endl;
    // }
    //m_jag.dump();





}