#ifndef MATRIX__HPP__
#define MATRIX__HPP__

#include <iostream>
#include "containers.hpp"

namespace matrix {

template <typename ArrT, typename T>
class Matrix {

private:
    size_t rows_;
    size_t cols_;
    ArrT matrix_;

    T *data () { return matrix_.data(); }

    struct ProxyRow final {
        T* row_;
        T& operator[](size_t col) { return row_[col]; }
        //получает столбец -- вторые []
        const T& operator[](size_t col) const { return row_[col]; }
    };

//coercion ctor && copy ctor
    // template <typename U, typename ArrT>
    // Matrix (const Matrix<U, ArrT> &rhs) {

    // }
public:

    //получает строку -- первые []
    ProxyRow operator[] (size_t n) {
        return ProxyRow{ matrix_.get_n_row(n * rows_) };
    }

    //filled with T
    Matrix(size_t rows, size_t cols, T val = T{}) : rows_(rows), cols_(cols), matrix_(rows, cols) {
        std::cout << "matrix value ctor " << std::endl;
        matrix_.fill(val);
    }
    
    //из заданной последовательности
    template <typename It>
    Matrix(size_t rows, size_t cols, It start, It fin) : rows_(rows), cols_(cols), matrix_(rows, cols) {
        std::cout << "matrix container ctor " << std::endl;
        matrix_.fill(start, fin);
    }


    //--------------- BIG FIVE --------------------
    Matrix(const Matrix &rhs) = default;
    Matrix(Matrix &&rhs) noexcept = default;
    Matrix& operator=(const Matrix &rhs) = default;
    Matrix& operator=(Matrix &&rhs) noexcept = default;

    //---------------------------------------------

    // bool equal(const Matrix& other) const {

    // }
    // void dump(std::ostream& os) const{

    // }

    //     void dump (std::ostream &out) const
    // {
    //     for (size_t i = 0; i < nRows_; ++i) {
    //         size_t row = nCols_ * i;
    //         for (size_t j = 0; j < nCols_; ++j)
    //             out << arr_[row + j] << " ";

    //         if (i + 1 != nRows_)
    //             out << std::endl;
    //     }
    // }

    // //-----------------------------------------------------------------------------------------------------

    // void input (std::istream &in)
    // {
    //     for (size_t i = 0, size = nRows_ * nCols_; i < size; ++i)
    //         in >> arr_[i];
    // }

    //to do -- dump
    size_t n_cols() const { return cols_; }
    size_t n_rows() const { return rows_; }
    size_t size() const { return cols_ * rows_; }

    virtual ~Matrix() = default;
};

//operator== -- equal
//operator << -- dump

template <typename ArrT, typename T>
class SquareMatrix final : public Matrix<ArrT, T> {

public:
    //filled with T
    SquareMatrix(size_t sz, T val = T{}) : Matrix<ArrT, T>(sz, sz, val) {}
    
    //из заданной последовательности
    template <typename It>
    SquareMatrix(size_t sz, It start, It fin) : Matrix<ArrT, T>(sz, sz, start, fin) {}

    static SquareMatrix eye(size_t sz) {
        std::cout << "matrix eye ctor " << std::endl;
    }


// //-------------- DETERMINANT CALCULATION -------------//
//     struct elem *max_elem(struct matrix *m, int col, int row) {

//         struct elem *max = NULL;
//         assert(m);

//         max = (struct elem *)calloc(1, sizeof(struct elem));

//         for(int i = row; i < m->size; ++i) {
//             for(int j = col; j < m->size; ++j) {
//                 if(fabs(m->arr[i][j]) > fabs(max->value)) {
//                     max->value = m->arr[i][j];
//                     max->row = i;
//                     max->col = j;
//                 }
//             }
//         }

//         return max;
//     }

//     void swap_rows(size_t row_1, size_t row_2) {
//         std::swap(matrix_[row_1], matrix_[row_2]);
//         // T *temp_row;
//         // temp_row = m->arr[row_1];
//         // m->arr[row_1] = m->arr[row_2];
//         // m->arr[row_2] = temp_row;
//     }

//     void swap_columns(size_t col_1, size_t col_2) {
        
//         double temp = 0.0;
//         for(int i = 0; i < m->size; ++i) {
//             temp = m->arr[i][col_1];
//             m->arr[i][col_1] = m->arr[i][col_2];
//             m->arr[i][col_2] = temp;
//         }
//     }


//     void eliminate(size_t row) {

//         double coef = 0.0;
//         for(int i = row + 1; i < m->size; ++i) {
//             coef = m->arr[i][row] / m->arr[row][row];
//             for(int j = row; j < m->size; ++j)
//                 m->arr[i][j] -= coef * m->arr[row][j];
//         }
//     }
//     //последняя строчка

//     T mult_diagonal() {
//         T diag = 1.0;
//         for(size_t i = 0; i < rows_; ++i)
//             diag *= matrix_[i][i];
        
//         return diag;
//     }

//     T calc_det() {
//         int res = 1;
//         int det = 0;
//         int i = 0;
//         int j = 0;
//         struct elem *max = NULL;
//         struct elem *pivot = NULL;
//         assert(m);

//         pivot = (struct elem *)calloc(1, sizeof(struct elem));

//         while(i < m->size - 1 && j < m->size - 1) {

//             max = max_elem(m, i, i);

//             if(dbl_cmp(max->value, 0.0) && i == 0)
//                 return 0;

//             pivot->row = max->row;
//             pivot->col = max->col;

//             free(max);

//             if(i != pivot->row) {
//                 swap_rows(m, i, pivot->row);
//                 res *= -1;
//             }
//             if(j != pivot->col) {
//                 swap_columns(m, j, pivot->col);
//                 res *= -1;
//             }

//             if(!dbl_cmp(m->arr[i][i], 0.0))
//                 eliminate(m, i);
//             ++i;
//             ++j;
//         }
//         free(pivot);
//         det = mult_diagonal(m) * res;
//         return det;
//     }


};

} //namespace matrix


namespace cmp {

int dbl_cmp(const double x, const double y) {
    const double epsilon = 10E-15;

    if (std::abs(x - y) < epsilon)
        return 0;
    if (x - y > 0)
        return 1;
    return -1;
}

}//namespace cmp

#endif //MATRIX__HPP__