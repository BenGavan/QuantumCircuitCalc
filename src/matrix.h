#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <complex>

class Matrix
{
    friend std::ostream &operator<<(std::ostream &os, const Matrix &m);
    friend std::istream &operator>>(std::istream &is, Matrix &m);
private:
    size_t number_of_rows, number_of_columns;
    std::complex<double>* elements{nullptr};

    size_t get_element_array_index(const size_t i, const size_t j) const
        { return (j) + (i)*number_of_columns; }
public:
    Matrix() : number_of_rows{0}, number_of_columns{0} {}
    Matrix(const size_t num_rows, const size_t num_cols);
    Matrix(const size_t num_rows, const size_t num_cols,
           const std::complex<double>* elements);
    Matrix(Matrix&);  // copy
    Matrix(Matrix&&); // move
    ~Matrix() { delete[] elements; }

    size_t get_number_of_rows() const { return number_of_rows; }
    size_t get_number_of_columns() const { return number_of_columns; }

    std::complex<double> get_element(const int &i, const int &j) const
        { return elements[get_element_array_index(i, j)]; }
    void set_element(const int &i, const int &j, const std::complex<double> &x)
        { elements[get_element_array_index(i, j)] = x; }

    std::complex<double> determinant() const;

    Matrix transpose() const;
    Matrix tensor_product(const Matrix &m) const;

    Matrix delete_row_and_column(const size_t row_i,
                                 const size_t column_j) const;

    std::complex<double> & operator()(const size_t i, const size_t j) const;

    Matrix operator+(const Matrix &m) const;
    Matrix operator-(const Matrix &m) const;
    Matrix operator*(const Matrix &m) const;

    Matrix& operator=(const Matrix&);  // copy assignment
    Matrix& operator=(Matrix&&);  // move assignment
};

#endif // MATRIX_H