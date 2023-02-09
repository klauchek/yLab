#ifndef MATRIX__HPP__
#define MATRIX__HPP__

#include <iostream>
#include "containers.hpp"

namespace matrix {

template <typename ArrT> class Matrix final {

private:
    size_t size_;
    ArrT matrix_;

//coercion ctor && copy ctor
    // template <typename U, typename ArrT>
    // Matrix (const Matrix<U, ArrT> &rhs) {

    // }

public:

    Matrix(size_t sz = 0) : size_(sz) {
        std::cout << "matrix ctor!" << std::endl;
    }
    size_t size() const { return size_; };
};

} //namespace matrix

#endif //MATRIX__HPP__