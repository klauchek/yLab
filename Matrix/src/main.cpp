#include "matrix.hpp"
#include <vector>

int main() {
    matrix::SquareMatrix<containers::Linear<int>, int> m_lin(3, 1);
    matrix::SquareMatrix<containers::Linear<int>, int> m_lin_2(5, 2);
   // matrix::SquareMatrix<containers::Jagged<int>, int> m_jag(5, 3);

    m_lin = m_lin_2;

    //propable for this we need cohersion ctor
    //m_lin = std::move(m_jag)


    // std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9};
    // matrix::SquareMatrix<containers::Linear<int>, int> m_lin(5, vec.begin(), vec.end());
    // //matrix::SquareMatrix<containers::Linear<int>, int> m_lin_2(5, 2);
    // matrix::SquareMatrix<containers::Jagged<int>, int> m_jag(5, 3);
    
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 5; ++j)
            std::cout << m_lin[i][j];
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // for(int i = 0; i < 5; ++i){
    //     for(int j = 0; j < 5; ++j)
    //         std::cout << m_jag[i][j];
    //     std::cout << std::endl;
    // }
    //m_jag.dump();
}