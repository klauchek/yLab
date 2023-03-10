#ifndef MATRIX__HPP__
#define MATRIX__HPP__

#include <iostream>
#include "containers.hpp"

namespace cmp {

int dbl_cmp(const double x, const double y) {
    const double epsilon = 10E-16;

    if (std::abs(x - y) < epsilon)
        return 0;
    if (x - y > 0)
        return 1;
    return -1;
}

}//namespace cmp


namespace matrix {

template <typename ArrT, typename T>
class Matrix {

protected:
    ArrT matrix_;
    size_t rows_;
    size_t cols_;

    struct ProxyRow final {
        T* row_;
        T& operator[](size_t col) { return row_[col]; }
        //получает столбец -- вторые []
        const T& operator[](size_t col) const { return row_[col]; }
    };

    //here iterator
    //make exeption safe 
    template <typename ArrU, typename U>    
    void copy(const Matrix<ArrU, U> &rhs) {
        for(size_t i = 0; i < rhs.n_rows(); ++i)
            for(size_t j = 0; j < rhs.n_cols(); ++j)
                matrix_[i * cols_ + j] = rhs[i][j];

        //copy in tmp
        //move from tmp
    }

public:

    //получает строку -- первые []
    ProxyRow operator[] (size_t n) {
        return ProxyRow{ matrix_.get_n_row(n * cols_) };
    }
    const ProxyRow operator[] (size_t n) const {
        return ProxyRow{ matrix_.get_n_row(n * cols_) };
    }
    

    //filled with T
    Matrix(size_t rows, size_t cols, T val = T{}) : matrix_(rows, cols), rows_(rows), cols_(cols) {
        std::cout << "matrix value ctor " << std::endl;
        matrix_.fill(val);
    }
    
    //из заданной последовательности
    template <typename It>
    Matrix(size_t rows, size_t cols, It start, It fin) : matrix_(rows, cols), rows_(rows), cols_(cols) {
        std::cout << "matrix container ctor " << std::endl;
        matrix_.fill(start, fin);
    }

    //coercion ctor
    //
    template <typename ArrU, typename U>
    Matrix (const Matrix<ArrU, U> &rhs) : Matrix<ArrT, T>(rhs.n_rows(), rhs.n_cols()) {
        std::cout << " Matr coercion " << std::endl;
        copy(rhs);
    }

    //--------------- BIG FIVE --------------------
    Matrix(const Matrix &rhs) = default;
    Matrix(Matrix &&rhs) noexcept = default;
    Matrix& operator=(const Matrix &rhs) = default;
    Matrix& operator=(Matrix &&rhs) noexcept = default;

    //---------------------------------------------

    void input (std::istream &in) {
        for (size_t i = 0, size = rows_ * cols_; i < size; ++i)
            in >> matrix_[i];
    }

    void dump (std::ostream &out) const {
        for (size_t i = 0; i < rows_; ++i) {
            size_t row = cols_ * i;
            for (size_t j = 0; j < cols_; ++j)
                out << matrix_[row + j] << " ";

            if (i + 1 != rows_)
                out << std::endl;
        }
    }

    bool equal (const Matrix<ArrT, T> &other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_)
            return false;

        return matrix_.equal(other.matrix_);
    }

    size_t n_cols() const { return cols_; }
    size_t n_rows() const { return rows_; }
    size_t size() const { return cols_ * rows_; }

    virtual ~Matrix() = default;
};

template <typename ArrT, typename T>
std::istream &operator>> (std::istream &in, Matrix<ArrT, T> &matrix){
    matrix.input(in);
    return in;
}

template <typename ArrT, typename T>
std::ostream &operator<< (std::ostream &out, const Matrix<ArrT, T> &matrix) {
    matrix.dump(out);
    return out;
}

template <typename ArrT, typename T>
bool operator == (const Matrix<ArrT, T> &lhs, const Matrix<ArrT, T> &rhs) {
    return lhs.equal(rhs);
}

template <typename ArrT, typename T>
class SquareMatrix final : public Matrix<ArrT, T> {

private:

    using Matrix<ArrT, T>::rows_;
    using Matrix<ArrT, T>::cols_;
    using Matrix<ArrT, T>::matrix_;

public:
//-------------------------- CONSTRUCTORS --------------------------//

    //filled with T
    SquareMatrix(size_t sz, T val = T{}) : Matrix<ArrT, T>(sz, sz, val) {}
    
    //из заданной последовательности
    template <typename It>
    SquareMatrix(size_t sz, It start, It fin) : Matrix<ArrT, T>(sz, sz, start, fin) {}

    template <typename ArrU, typename U>
    SquareMatrix (const SquareMatrix<ArrU, U> &rhs) : Matrix<ArrT, T>(rhs) {}

    static SquareMatrix eye(size_t sz) {
        std::cout << "matrix eye ctor " << std::endl;
        SquareMatrix<ArrT, T> matr {sz};
        for(size_t i = 0; i < sz; ++i)
            matr[i][i] = T{1};

        return matr;
    }

    struct Elem {
        T value;
        size_t row;
        size_t col;
    };

//--------------------- DETERMINANT CALCULATION --------------------//
//standard algo
//private
    Elem max_elem(size_t row, size_t col) const {

        Elem max {};
        for(size_t i = row; i < rows_; ++i) {
            T* start = matrix_.get_n_row(i * cols_) + col;
            T* fin = matrix_.get_n_row(i * cols_) + cols_;
            auto* res = std::max_element(start, fin, cmp::dbl_cmp);

            if (cmp::dbl_cmp(std::abs(*res), std::abs(max.value)) > 0) {
                max.value = *res;
                max.row = i;
                max.col = col + std::distance(start, res);
            }
        }

        return max;
    }

    void swap_rows(size_t row_1, size_t row_2) {
        auto* first = matrix_.get_n_row(row_1 * cols_);
        auto* second = matrix_.get_n_row(row_2 * cols_);
        std::swap_ranges(first, first + cols_, second);
    }

    void swap_columns(size_t col_1, size_t col_2) {
        for(int i = 0; i < rows_; ++i) {
            size_t row_beg = i * cols_;
            std::swap(matrix_[row_beg + col_1], matrix_[row_beg + col_2]);
        }
    }

    void eliminate(size_t row) {
        double coef = 0.0;
        for(size_t i = row + 1; i < rows_; ++i) {
            coef = matrix_[i * cols_ + row] / matrix_[row * cols_ + row];
            for(size_t j = row; j < cols_; ++j)
                matrix_[i * cols_ + j] -= coef * matrix_[row * cols_ + j];
        }
    }

    double mult_diagonal() const {
        double diag = 1.0;
        for(size_t i = 0; i < rows_; ++i)
            diag *= matrix_[i * cols_ + i];

        return cmp::dbl_cmp(diag, 0.0) ? diag : 0.0;
    }
//tp do const
    T calc_det() {
        int sign = 1;
        size_t i {};
        size_t j {};
        //tmp matrix

        while(i < rows_ - 1 && j < cols_ - 1) {
            Elem pivot = max_elem(i, i);

            if(cmp::dbl_cmp(pivot.value, 0.0) == 0 && i == 0)
                return 0;

            if(i != pivot.row) {
                swap_rows(i, pivot.row);
                sign *= -1;
            }
            if(j != pivot.col) {
                swap_columns(j, pivot.col);
                sign *= -1;
            }

            if(cmp::dbl_cmp(matrix_[i * cols_ + i], 0.0) != 0)
                eliminate(i);
            ++i;
            ++j;
        }
        std::cout << *this << std::endl;
        T det = mult_diagonal() * sign;
        return det;
    }


};

} //namespace matrix

#endif //MATRIX__HPP__