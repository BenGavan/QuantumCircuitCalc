#include "matrix.h"
#include <string>

Matrix::Matrix(const size_t num_rows, const size_t num_cols)
{
    if (num_rows < 1 || num_cols < 1) {
        std::cout << "Error: Trying to declare a Matrix with "
                     "at least one dimension < 1" << std::endl;
        throw("size of Matrix not positive");
    }
    number_of_rows = num_rows;
    number_of_columns = num_cols;

    const size_t num_elements = num_rows * num_cols;

    elements = new std::complex<double>[num_elements];
    for (size_t i{0}; i<num_elements; i++) {  // set Matrix elements = 0
        elements[i] = 0;
    }
}

Matrix::Matrix(const size_t num_rows, const size_t num_cols,
               const std::complex<double>* elements_to_copy)
{
    if (num_rows < 1 || num_cols < 1) {
        std::cout << "Error: Trying to declare a Matrix with "
                     "at least one dimension < 1" << std::endl;
        throw("size of Matrix not positive");
    }

    number_of_rows = num_rows;
    number_of_columns = num_cols;

    const size_t num_elements = num_rows * num_cols;

    elements = new std::complex<double>[num_elements];

    for (size_t i{0}; i<num_elements; i++) {
        elements[i] = elements_to_copy[i];
    }
}

Matrix::Matrix(Matrix &matrix_to_copy)
// copy constructor (using deep copying)
{
    number_of_rows = matrix_to_copy.number_of_rows;
    number_of_columns = matrix_to_copy.number_of_columns;
    elements = nullptr;

    const size_t number_of_elements = number_of_rows * number_of_columns;

    if (number_of_elements > 0) {
        elements = new std::complex<double>[number_of_elements];
        for (size_t i{0}; i<number_of_elements; i++) {
            elements[i] = matrix_to_copy.elements[i];
        }
    }
}

Matrix::Matrix(Matrix &&matrix_to_move)
// move constructor
{
    number_of_rows = matrix_to_move.number_of_rows;
    number_of_columns = matrix_to_move.number_of_columns;
    elements = matrix_to_move.elements;

    matrix_to_move.number_of_rows = 0;
    matrix_to_move.number_of_columns = 0;
    matrix_to_move.elements = nullptr;
}

std::complex<double> & Matrix::operator()(const size_t i, const size_t j) const {
    if (i<0 || i>number_of_rows || j<0 || j>number_of_columns) {
        std::cout << "Error: trying to access element out of bounds"
            << std::endl;
        throw("out of bounds error");
    }
    return elements[get_element_array_index(i, j)];
}

std::complex<double> Matrix::determinant() const {
    if (number_of_rows == 1 && number_of_columns == 1) {
        return (*this)(0, 0);
    }

    std::complex<double> det{0};

    for (size_t j{0}; j<=number_of_columns; j++) {
        det += std::pow(-1, j) * (*this)(0, j)
                * delete_row_and_column(0, j).determinant();
    }

    return det;
}

Matrix Matrix::transpose() const {
    Matrix new_m{number_of_rows, number_of_columns};
    for (size_t i{0}; i<number_of_rows; i++) {
        for (size_t j{0}; j<number_of_columns; j++) {
            new_m(i, j) = (*this)(j, i);
        }
    }
    return new_m;
}

Matrix Matrix::tensor_product(const Matrix &m) const {
    Matrix new_m{number_of_rows * m.number_of_rows, number_of_columns * m.number_of_columns};
    for (size_t i{0}; i<number_of_rows; i++) {
        for (size_t j{0}; j<number_of_columns; j++) {
            for (size_t k{0}; k<number_of_rows; k++) {
                for (size_t l{0}; l<number_of_columns; l++) {
                    new_m(i*number_of_rows + k, j*number_of_columns + l) = (*this)(i, j) * m(k, l);
                }
            }
        }
    }
    return new_m;
}

Matrix Matrix::delete_row_and_column(const size_t row_to_delete,
                                     const size_t column_to_delete) const {
    if (row_to_delete > number_of_rows || row_to_delete < 0
            || column_to_delete > number_of_columns || column_to_delete < 0) {
        std::cout << "Error: row or column deletion index out of range."
            << std::endl;
        throw("invalid deletion index");
    }

    Matrix new_matrix{number_of_rows-1, number_of_columns-1};

    size_t i_new;
    size_t j_new;

    for (size_t i{0}; i<number_of_rows; i++) {
        for (size_t j{0}; j<number_of_columns; j++) {

            if (i == row_to_delete || j == column_to_delete) continue;

            i_new = (i < row_to_delete) ? i : i-1;
            j_new = (j < column_to_delete) ? j : j-1;

            new_matrix(i_new, j_new) = (*this)(i, j);
        }
    }

    return new_matrix;
}

Matrix Matrix::operator+(const Matrix &m) const {
    Matrix new_matrix{number_of_rows, number_of_columns};

    if (m.number_of_rows != number_of_rows
        || m.number_of_columns != number_of_columns) {
        std::cout << "Number of rows & columns must be equal for matrix "
                     "addition (" << m.number_of_rows << ", "
                     << m.number_of_columns <<  ") ?= ("
        << number_of_rows << ", " << number_of_columns <<  ")" << std::endl;
        throw("matrix shapes need to be equal for matrix addition");
    }

    for (int i{0}; i<number_of_rows; i++) {
        for (int j{0}; j<number_of_columns; j++) {
            new_matrix(i, j) = (*this)(i, j) + m(i, j);
        }
    }

    return new_matrix;
}

Matrix Matrix::operator-(const Matrix &m) const {
    Matrix new_matrix{number_of_rows, number_of_columns};

    if (m.number_of_rows != number_of_rows
        || m.number_of_columns != number_of_columns) {
        std::cout << "Number of rows & columns must be equal for matrix "
                     "addition (" << m.number_of_rows << ", "
                     << m.number_of_columns <<  ") ?= (" << number_of_rows
                     << ", " << number_of_columns <<  ")" << std::endl;
        throw("matrix shapes need to be equal for matrix subtraction");
    }

    for (int i{0}; i<number_of_rows; i++) {
        for (int j{0}; j<number_of_columns; j++) {
            new_matrix(i, j) = (*this)(i, j) - m(i, j);
        }
    }

    return new_matrix;
}

Matrix Matrix::operator*(const Matrix &m) const {
    Matrix new_matrix{number_of_rows, m.number_of_columns};

    if (number_of_columns != m.number_of_rows) {
        std::cout << "Error: matrix multiplication condition: "
                     "(n*m)(m*l) violated." << std::endl;
        throw("matrix multiplication condition: (n*m)(m*l) violated");
    }
    // a_{ij} * b_{jk}
    for (size_t i{0}; i<number_of_rows; i++) {
        for (size_t j{0}; j<number_of_columns; j++) {
            for (size_t k{0}; k<m.number_of_columns; k++) {
                new_matrix(i, k) += (*this)(i, j) * m(j, k);
            }
        }
    }

    return new_matrix;
}

Matrix & Matrix::operator=(const Matrix &rhs_matrix)
// Assignment operator (using deep copying)
{
    if (&rhs_matrix == this) return *this;  // no self assignment

    // delete/reset this
    delete[] elements;
    elements = nullptr;

    number_of_rows = rhs_matrix.number_of_rows;
    number_of_columns = rhs_matrix.number_of_columns;

    const size_t number_of_elements = number_of_rows * number_of_columns;

    elements = new std::complex<double>[number_of_elements];

    // copy rhs matrix values into new array
    for (size_t i{0}; i<number_of_elements; i++) {
        elements[i] = rhs_matrix.elements[i];
    }

    return *this;
}

// Move assignment operator 
Matrix & Matrix::operator=(Matrix &&rhs_matrix) {
    if (&rhs_matrix == this) return *this;  // no self assignment

    number_of_rows = rhs_matrix.number_of_rows;
    number_of_columns = rhs_matrix.number_of_columns;
    elements = rhs_matrix.elements;

    rhs_matrix.number_of_rows = 0;
    rhs_matrix.number_of_columns = 0;
    rhs_matrix.elements = nullptr;

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Matrix &m) {
    // max number of characters in a row

    // std::to_string(1.1);
    // int max_row_chars = 0;
    // for (size_t i{1}; i<=m.number_of_rows; i++) {
    //     int row_chars = 0;
    //     for (size_t j{1}; j<=m.number_of_columns; j++) {
    //         row_chars += std::to_string(m(i, j)).length();
    //     }
        
    // }

    // top line
    // os << "┌";
    // for (size_t i{0}; i<max_row_chars; i++) {  // TODO: Calculate the max number of characters accross
    //     os << " ";        
    // }
    // os << "┐\n";

    // content and side lines
    for (size_t i{0}; i<m.number_of_rows; i++) {
        os << "│";
        for (size_t j{0}; j<m.number_of_columns; j++) {
            os << m.get_element(i, j) << ' ';
        }
        os << "│\n";
    }

    // bottom line
    // os << "└";
    // for (size_t i{0}; i<max_row_chars; i++) {  // TODO: Calculate the max number of characters accross
    //     os << " ";        
    // }
    // os << "┘\n";
    return os;
}

std::istream &operator>>(std::istream &is, Matrix &m) {
    is >> m.number_of_rows >> m.number_of_columns;

    const size_t number_of_elements = m.number_of_rows * m.number_of_columns;

    delete[] m.elements;

    m.elements = new std::complex<double>[number_of_elements];

    for (size_t i{0}; i<number_of_elements; i++) {
        is >> m.elements[i];
    }

    return is;
}

void demonstrate_operations(const Matrix &a, const Matrix &b, const Matrix &c) {
    std::cout << "------------------------\n";
    std::cout << "Operations demonstration\n";
    std::cout << "------------------------\n";
    std::cout << "A+B = \n" << a+b << "--------" << std::endl;

    std::cout << "A-B = \n" << a-b << "--------" << std::endl;

    std::cout << "A.B = \n" << a*b << "--------" << std::endl;

    std::cout << "C.B = \n" << c*b << "--------" << std::endl;

    try {
        std::cout << "B.C = \n" << b*c;
    } catch (...) {
        std::cout << "Recovering from invalid matrix shapes for multiplication"
                     " (B.C)" << std::endl;
    }

    std::cout << std::endl;
}

void demonstrate_determinant(const Matrix &a, const Matrix &b) {
    std::cout << "-------------------------\n";
    std::cout << "Determinant demonstration\n";
    std::cout << "-------------------------\n";
    std::cout << "Determinant of matrix A = " << a.determinant() << std::endl;
    std::cout << "Determinant of matrix B = " << b.determinant() << std::endl;
    std::cout << std::endl;
}

void demonstrate_row_and_column_deletion(const Matrix &a)
{
    std::cout << "-------------------------------------\n";
    std::cout << "Row and Column deletion demonstration\n";
    std::cout << "-------------------------------------\n";
    std::cout << "Matrix A with no deletions: \n" << a << "------" << std::endl;
    std::cout << "Matrix A with row 1 and column 2 deleted: \n"
        << a.delete_row_and_column(1, 2) << "----" << std::endl;
    std::cout << "Matrix A with row 2 and column 2 deleted: \n"
        << a.delete_row_and_column(2, 2) << "----" << std::endl;
    std::cout << "Matrix A with row 3 and column 3 deleted: \n"
        << a.delete_row_and_column(3, 3) << "----" << std::endl;
    std::cout << "Matrix A with row 3 and column 1 deleted: \n"
        << a.delete_row_and_column(3, 1) << "----" << std::endl;
    std::cout << std::endl;
}

void demonstrate_copy_constructor()
{
    std::cout << "------------------------------\n";
    std::cout << "Copy constructor demonstration\n";
    std::cout << "------------------------------\n";

    const std::complex<double> a_elements[9] = {1, 2, 3, 9, 8, 7, 4, 2, 6};
    Matrix a{3, 3, a_elements};

    std::cout << "Original A (before modifications) = \n" << a << "------\n";

    // copy constructor on A
    std::cout << "* Copying matrix A" << std::endl;
    Matrix a_copy{a};

    // modify the original matrix
    // make diagonal negative
    a(0, 0) = -a(0, 0);
    a(1, 1) = -a(1, 1);
    a(2, 2) = -a(2, 2);

    a(0, 2) = 99;

    // output both original and its copy
    std::cout << "Original A (after modifications) = \n" << a << "------\n";
    std::cout << "Copy of A (copied before the modifications) = \n" << a_copy
        << "------\n";
    std::cout << std::endl;
}

void demonstrate_copy_assignment()
{
    std::cout << "------------------------------\n";
    std::cout << "Copy assignment assignment\n";
    std::cout << "------------------------------\n";

    const std::complex<double> a_elements[9] = {1, 2, 3, 9, 8, 7, 4, 2, 6};
    Matrix a{3, 3, a_elements};

    std::cout << "Original A (before modifications) = \n" << a << "------\n";

    // copy constructor on A
    std::cout << "* Copying matrix A" << std::endl;
    Matrix a_copy;

    a_copy = a;

    // modify the original matrix
    // make diagonal negative
    a(1, 1) = -a(1, 1);
    a(2, 2) = -a(2, 2);
    a(3, 3) = -a(3, 3);

    a(1, 3) = 99;

    // output both original and its copy
    std::cout << "Original A (after modifications) = \n" << a << "------\n";
    std::cout << "Copy of A (copied before the modifications) = \n" << a_copy
        << "------\n";
    std::cout << std::endl;
}

void demonstrate_move_constructor() {
    std::cout << "------------------------------\n";
    std::cout << "Move constructor demonstration\n";
    std::cout << "------------------------------\n";

    const std::complex<double> a_elements[9] = {1, 2, 3, 9, 8, 7, 4, 2, 6};
    Matrix matrix_a{3, 3, a_elements};

    std::cout << "Original A (before move) = \n" << matrix_a << "------\n";

    // move constructor on A
    std::cout << "* Moving matrix A to matrix M" << std::endl;
    Matrix matrix_m{std::move(matrix_a)};

    std::cout << "Original A (after move) = \n" << matrix_a << "------\n";
    std::cout << "Shape of original A (after move) = ("
        << matrix_a.get_number_of_rows() << ", "
        << matrix_a.get_number_of_columns() << ")" << std::endl;
    std::cout << " -> still in valid state" << std::endl;

    std::cout << "Matrix M (after move from A) = \n" << matrix_m << "------\n";
    std::cout << "Shape of Matrix M = (" << matrix_m.get_number_of_rows()
        << ", " << matrix_m.get_number_of_columns() << ")" << std::endl;
    std::cout << std::endl;
}

void demonstrate_move_assignment() {
    std::cout << "------------------------------\n";
    std::cout << "Move assignment demonstration\n";
    std::cout << "------------------------------\n";

    const std::complex<double> a_elements[9] = {1, 2, 3, 9, 8, 7, 4, 2, 6};
    Matrix a{3, 3, a_elements};

    std::cout << "Original A (before move) = \n" << a << "------\n";

    // move constructor on A
    std::cout << "* Moving matrix A to matrix M" << std::endl;
    Matrix matrix_m;
    matrix_m = std::move(a);

    std::cout << "Original A (after move) = \n" << a << "------\n";
    std::cout << "Shape of original A (after move) = ("
        << a.get_number_of_rows() << ", " << a.get_number_of_columns()
        << ")" << std::endl;
    std::cout << " -> still in valid state" << std::endl;

    std::cout << "Matrix M (after move from A) = \n" << matrix_m << "------\n";
    std::cout << "Shape of Matrix M = (" << matrix_m.get_number_of_rows()
        << ", " << matrix_m.get_number_of_columns() << ")" << std::endl;

    std::cout << "* Testing self assigment" << std::endl;
    matrix_m = std::move(matrix_m);  // test self assignment

    std::cout << "Matrix M (after self assignment) = \n" << matrix_m
        << "------\n";
    std::cout << "Shape of Matrix M = (" << matrix_m.get_number_of_rows()
        << ", " << matrix_m.get_number_of_columns() << ")" << std::endl;
    std::cout << std::endl;
}

void demonstrate_matrix_instream()
{
    std::cout << "-----------------------------------------------\n";
    std::cout << "Matrix construction from instream demonstration\n";
    std::cout << "To: \"show that you can read in the matrix A\"\n";
    std::cout << "-----------------------------------------------\n";

    Matrix matrix_in;
    std::cout << "Enter a matrix in the form of of a space separated list:"
                 " {number_of_rows} {number_of_columns} {element_11} "
                 "{element_12} ... {element_nm}" << std::endl;
    std::cin >> matrix_in;  // e.g. for a 2D identity = 2 2 1 0 0 1

    std::cout << "The matrix, M, you entered has the shape: ("
        << matrix_in.get_number_of_rows() << ", "
        << matrix_in.get_number_of_columns() << ") with elements:\n"
        << matrix_in;

    if (matrix_in.get_number_of_rows() == matrix_in.get_number_of_columns()) {
        std::cout << "det(M) = " << matrix_in.determinant() << std::endl;
        std::cout << "M^2 = \n" << matrix_in * matrix_in;
    }

    std::cout << std::endl;
}

// int main()
// {
//     std::cout << "-------------------\n";
//     std::cout << "Matrices being used\n";
//     std::cout << "-------------------" << std::endl;

//     double a_elements[9] = {1, 2, 3, 9, 8, 7, 4, 2, 6};
//     matrix matrix_a{3, 3, a_elements};

//     std::cout << "Matrix A:\n" << matrix_a << "-----"<< std::endl;

//     double b_elements[9] = {5, 5, 4, 1, 2, 3, 6, 9, 8};
//     matrix matrix_b{3, 3, b_elements};

//     std::cout << "Matrix B:\n" << matrix_b << "-----"<< std::endl;

//     double c_elements[6] = {3, 4, 1, 2, 5, 6};
//     matrix matrix_c{2, 3, c_elements};

//     std::cout << "Matrix C:\n" << matrix_c << "-----"<< std::endl;
//     std::cout << std::endl;

//     demonstrate_operations(matrix_a, matrix_b, matrix_c);
//     demonstrate_determinant(matrix_a, matrix_b);
//     demonstrate_row_and_column_deletion(matrix_a);
//     demonstrate_copy_constructor();
//     demonstrate_copy_assignment();
//     demonstrate_move_constructor();
//     demonstrate_move_assignment();
//     demonstrate_matrix_instream();

//     return 0;
// }



// #include "matrix.h"

// template<class T>
// matrix<T>::matrix(const size_t num_rows, const size_t num_cols)
// {
//     if (num_rows < 1 || num_cols < 1) {
//         std::cout << "Error: Trying to declare a matrix with "
//                      "at least one dimension < 1" << std::endl;
//         throw("size of matrix not positive");
//     }
//     number_of_rows = num_rows;
//     number_of_columns = num_cols;

//     const size_t num_elements = num_rows * num_cols;

//     elements = new T[num_elements];
//     for (size_t i{0}; i<num_elements; i++) {  // set matrix elements = 0
//         elements[i] = 0;
//     }
// }

// template<class T>
// matrix<T>::matrix(const size_t num_rows, const size_t num_cols,
//                const T* elements_to_copy)
// {
//     if (num_rows < 1 || num_cols < 1) {
//         std::cout << "Error: Trying to declare a matrix with "
//                      "at least one dimension < 1" << std::endl;
//         throw("size of matrix not positive");
//     }

//     number_of_rows = num_rows;
//     number_of_columns = num_cols;

//     const size_t num_elements = num_rows * num_cols;

//     elements = new double[num_elements];

//     for (size_t i{0}; i<num_elements; i++) {
//         elements[i] = elements_to_copy[i];
//     }
// }

// template<class T>
// matrix<T>::matrix(matrix &matrix_to_copy)
// // copy constructor (using deep copying)
// {
//     number_of_rows = matrix_to_copy.number_of_rows;
//     number_of_columns = matrix_to_copy.number_of_columns;
//     elements = nullptr;

//     const size_t number_of_elements = number_of_rows * number_of_columns;

//     if (number_of_elements > 0) {
//         elements = new double[number_of_elements];
//         for (size_t i{0}; i<number_of_elements; i++) {
//             elements[i] = matrix_to_copy.elements[i];
//         }
//     }
// }

// template<class T>
// matrix<T>::matrix(matrix &&matrix_to_move)
// // move constructor
// {
//     number_of_rows = matrix_to_move.number_of_rows;
//     number_of_columns = matrix_to_move.number_of_columns;
//     elements = matrix_to_move.elements;

//     matrix_to_move.number_of_rows = 0;
//     matrix_to_move.number_of_columns = 0;
//     matrix_to_move.elements = nullptr;
// }

// template<class T>
// T & matrix<T>::operator()(const size_t i, const size_t j) const
// {
//     if (i<1 || i>number_of_rows || j<1 || j>number_of_columns) {
//         std::cout << "Error: trying to access element out of bounds"
//             << std::endl;
//         throw("out of bounds error");
//     }
//     return elements[get_element_array_index(i, j)];
// }

// template<class T>
// T matrix<T>::determinant() const {
//     if (number_of_rows == 1 && number_of_columns == 1) {
//         return (*this)(1, 1);
//     }

//     T det{0};

//     for (size_t j{1}; j<=number_of_columns; j++) {
//         det += std::pow(-1, j+1) * (*this)(1, j)
//                 * delete_row_and_column(1, j).determinant();
//     }

//     return det;
// }

// template<class T>
// matrix<T> matrix<T>::delete_row_and_column(const size_t row_to_delete,
//                                      const size_t column_to_delete) const {
//     if (row_to_delete > number_of_rows || row_to_delete < 1
//             || column_to_delete > number_of_columns || column_to_delete < 1) {
//         std::cout << "Error: row or column deletion index out of range."
//             << std::endl;
//         throw("invalid deletion index");
//     }

//     matrix new_matrix{number_of_rows-1, number_of_columns-1};

//     size_t i_new;
//     size_t j_new;

//     for (size_t i{1}; i<=number_of_rows; i++) {
//         for (size_t j{1}; j<=number_of_columns; j++) {

//             if (i == row_to_delete || j == column_to_delete) continue;

//             i_new = (i < row_to_delete) ? i : i-1;
//             j_new = (j < column_to_delete) ? j : j-1;

//             new_matrix(i_new, j_new) = (*this)(i, j);
//         }
//     }

//     return new_matrix;
// }

// template<class T>
// matrix<T> matrix<T>::operator+(const matrix &m) const {
//     matrix new_matrix{number_of_rows, number_of_columns};

//     if (m.number_of_rows != number_of_rows
//         || m.number_of_columns != number_of_columns) {
//         std::cout << "Number of rows & columns must be equal for matrix "
//                      "addition (" << m.number_of_rows << ", "
//                      << m.number_of_columns <<  ") ?= ("
//         << number_of_rows << ", " << number_of_columns <<  ")" << std::endl;
//         throw("matrix shapes need to be equal for matrix addition");
//     }

//     for (int i{1}; i<=number_of_rows; i++) {
//         for (int j{1}; j<=number_of_columns; j++) {
//             new_matrix(i, j) = (*this)(i, j) + m(i, j);
//         }
//     }

//     return new_matrix;
// }

// template<class T>
// matrix<T> matrix<T>::operator-(const matrix &m) const {
//     matrix new_matrix{number_of_rows, number_of_columns};

//     if (m.number_of_rows != number_of_rows
//         || m.number_of_columns != number_of_columns) {
//         std::cout << "Number of rows & columns must be equal for matrix "
//                      "addition (" << m.number_of_rows << ", "
//                      << m.number_of_columns <<  ") ?= (" << number_of_rows
//                      << ", " << number_of_columns <<  ")" << std::endl;
//         throw("matrix shapes need to be equal for matrix subtraction");
//     }

//     for (int i{1}; i<=number_of_rows; i++) {
//         for (int j{1}; j<=number_of_columns; j++) {
//             new_matrix(i, j) = (*this)(i, j) - m(i, j);
//         }
//     }

//     return new_matrix;
// }

// template<class T>
// matrix<T> matrix<T>::operator*(const matrix<T> &m) const {
//     matrix new_matrix{number_of_rows, m.number_of_columns};

//     if (number_of_columns != m.number_of_rows) {
//         std::cout << "Error: matrix multiplication condition: "
//                      "(n*m)(m*l) violated." << std::endl;
//         throw("matrix multiplication condition: (n*m)(m*l) violated");
//     }
//     // a_{ij} * b_{jk}
//     for (size_t i{1}; i<=number_of_rows; i++) {
//         for (size_t j{1}; j<=number_of_columns; j++) {
//             for (size_t k{1}; k<=m.number_of_columns; k++) {
//                 new_matrix(i, k) += (*this)(i, j) * m(j, k);
//             }
//         }
//     }

//     return new_matrix;
// }

// template<class T>
// matrix<T> & matrix<T>::operator=(const matrix<T> &rhs_matrix)
// // Assignment operator (using deep copying)
// {
//     if (&rhs_matrix == this) return *this;  // no self assignment

//     // delete/reset this
//     delete[] elements;
//     elements = nullptr;

//     number_of_rows = rhs_matrix.number_of_rows;
//     number_of_columns = rhs_matrix.number_of_columns;

//     const size_t number_of_elements = number_of_rows * number_of_columns;

//     elements = new double[number_of_elements];

//     // copy rhs matrix values into new array
//     for (size_t i{0}; i<number_of_elements; i++) {
//         elements[i] = rhs_matrix.elements[i];
//     }

//     return *this;
// }

// // Move assignment operator 
// template<class T>
// matrix<T> & matrix<T>::operator=(matrix<T> &&rhs_matrix) {
//     if (&rhs_matrix == this) return *this;  // no self assignment

//     number_of_rows = rhs_matrix.number_of_rows;
//     number_of_columns = rhs_matrix.number_of_columns;
//     elements = rhs_matrix.elements;

//     rhs_matrix.number_of_rows = 0;
//     rhs_matrix.number_of_columns = 0;
//     rhs_matrix.elements = nullptr;

//     return *this;
// }

// template<class T>
// std::ostream &operator<<(std::ostream &os, const matrix<T> &m) {
//     for (size_t i{1}; i<=m.number_of_rows; i++) {
//         for (size_t j{1}; j<=m.number_of_columns; j++) {
//             std::cout << m.get_element(i, j) << ' ';
//         }
//         std::cout << '\n';
//     }
//     return os;
// }

// template<class T>
// std::istream &operator>>(std::istream &is, matrix<T> &m) {
//     is >> m.number_of_rows >> m.number_of_columns;

//     const size_t number_of_elements = m.number_of_rows * m.number_of_columns;

//     delete[] m.elements;

//     m.elements = new double[number_of_elements];

//     for (size_t i{0}; i<number_of_elements; i++) {
//         is >> m.elements[i];
//     }

//     return is;
// }

// void demonstrate_operations(const Matrix &a, const Matrix &b, const Matrix &c) {
//     std::cout << "------------------------\n";
//     std::cout << "Operations demonstration\n";
//     std::cout << "------------------------\n";
//     std::cout << "A+B = \n" << a+b << "--------" << std::endl;

//     std::cout << "A-B = \n" << a-b << "--------" << std::endl;

//     std::cout << "A.B = \n" << a*b << "--------" << std::endl;

//     std::cout << "C.B = \n" << c*b << "--------" << std::endl;

//     try {
//         std::cout << "B.C = \n" << b*c;
//     } catch (...) {
//         std::cout << "Recovering from invalid matrix shapes for multiplication"
//                      " (B.C)" << std::endl;
//     }

//     std::cout << std::endl;
// }

// void demonstrate_determinant(const matrix<double> &a, const matrix<double> &b) {
//     std::cout << "-------------------------\n";
//     std::cout << "Determinant demonstration\n";
//     std::cout << "-------------------------\n";
//     std::cout << "Determinant of matrix A = " << a.determinant() << std::endl;
//     std::cout << "Determinant of matrix B = " << b.determinant() << std::endl;
//     std::cout << std::endl;
// }

// void demonstrate_row_and_column_deletion(const matrix<double> &a)
// {
//     std::cout << "-------------------------------------\n";
//     std::cout << "Row and Column deletion demonstration\n";
//     std::cout << "-------------------------------------\n";
//     std::cout << "Matrix A with no deletions: \n" << a << "------" << std::endl;
//     std::cout << "Matrix A with row 1 and column 2 deleted: \n"
//         << a.delete_row_and_column(1, 2) << "----" << std::endl;
//     std::cout << "Matrix A with row 2 and column 2 deleted: \n"
//         << a.delete_row_and_column(2, 2) << "----" << std::endl;
//     std::cout << "Matrix A with row 3 and column 3 deleted: \n"
//         << a.delete_row_and_column(3, 3) << "----" << std::endl;
//     std::cout << "Matrix A with row 3 and column 1 deleted: \n"
//         << a.delete_row_and_column(3, 1) << "----" << std::endl;
//     std::cout << std::endl;
// }

// void demonstrate_copy_constructor()
// {
//     std::cout << "------------------------------\n";
//     std::cout << "Copy constructor demonstration\n";
//     std::cout << "------------------------------\n";

//     const double a_elements[9] = {1, 2, 3, 9, 8, 7, 4, 2, 6};
//     matrix<double> a{3, 3, a_elements};

//     std::cout << "Original A (before modifications) = \n" << a << "------\n";

//     // copy constructor on A
//     std::cout << "* Copying matrix A" << std::endl;
//     matrix<double> a_copy{a};

//     // modify the original matrix
//     // make diagonal negative
//     a(1, 1) = -a(1, 1);
//     a(2, 2) = -a(2, 2);
//     a(3, 3) = -a(3, 3);

//     a(1, 3) = 99;

//     // output both original and its copy
//     std::cout << "Original A (after modifications) = \n" << a << "------\n";
//     std::cout << "Copy of A (copied before the modifications) = \n" << a_copy
//         << "------\n";
//     std::cout << std::endl;
// }

// void demonstrate_copy_assignment()
// {
//     std::cout << "------------------------------\n";
//     std::cout << "Copy assignment assignment\n";
//     std::cout << "------------------------------\n";

//     const double a_elements[9] = {1, 2, 3, 9, 8, 7, 4, 2, 6};
//     matrix<double> a{3, 3, a_elements};

//     std::cout << "Original A (before modifications) = \n" << a << "------\n";

//     // copy constructor on A
//     std::cout << "* Copying matrix A" << std::endl;
//     matrix<double> a_copy;

//     a_copy = a;

//     // modify the original matrix
//     // make diagonal negative
//     a(1, 1) = -a(1, 1);
//     a(2, 2) = -a(2, 2);
//     a(3, 3) = -a(3, 3);

//     a(1, 3) = 99;

//     // output both original and its copy
//     std::cout << "Original A (after modifications) = \n" << a << "------\n";
//     std::cout << "Copy of A (copied before the modifications) = \n" << a_copy
//         << "------\n";
//     std::cout << std::endl;
// }

// void demonstrate_move_constructor() {
//     std::cout << "------------------------------\n";
//     std::cout << "Move constructor demonstration\n";
//     std::cout << "------------------------------\n";

//     const double a_elements[9] = {1, 2, 3, 9, 8, 7, 4, 2, 6};
//     matrix<double> matrix_a{3, 3, a_elements};

//     std::cout << "Original A (before move) = \n" << matrix_a << "------\n";

//     // move constructor on A
//     std::cout << "* Moving matrix A to matrix M" << std::endl;
//     matrix<double> matrix_m{std::move(matrix_a)};

//     std::cout << "Original A (after move) = \n" << matrix_a << "------\n";
//     std::cout << "Shape of original A (after move) = ("
//         << matrix_a.get_number_of_rows() << ", "
//         << matrix_a.get_number_of_columns() << ")" << std::endl;
//     std::cout << " -> still in valid state" << std::endl;

//     std::cout << "Matrix M (after move from A) = \n" << matrix_m << "------\n";
//     std::cout << "Shape of Matrix M = (" << matrix_m.get_number_of_rows()
//         << ", " << matrix_m.get_number_of_columns() << ")" << std::endl;
//     std::cout << std::endl;
// }

// void demonstrate_move_assignment() {
//     std::cout << "------------------------------\n";
//     std::cout << "Move assignment demonstration\n";
//     std::cout << "------------------------------\n";

//     const double a_elements[9] = {1, 2, 3, 9, 8, 7, 4, 2, 6};
//     matrix<double> a{3, 3, a_elements};

//     std::cout << "Original A (before move) = \n" << a << "------\n";

//     // move constructor on A
//     std::cout << "* Moving matrix A to matrix M" << std::endl;
//     matrix<double> matrix_m;
//     matrix_m = std::move(a);

//     std::cout << "Original A (after move) = \n" << a << "------\n";
//     std::cout << "Shape of original A (after move) = ("
//         << a.get_number_of_rows() << ", " << a.get_number_of_columns()
//         << ")" << std::endl;
//     std::cout << " -> still in valid state" << std::endl;

//     std::cout << "Matrix M (after move from A) = \n" << matrix_m << "------\n";
//     std::cout << "Shape of Matrix M = (" << matrix_m.get_number_of_rows()
//         << ", " << matrix_m.get_number_of_columns() << ")" << std::endl;

//     std::cout << "* Testing self assigment" << std::endl;
//     matrix_m = std::move(matrix_m);  // test self assignment

//     std::cout << "Matrix M (after self assignment) = \n" << matrix_m
//         << "------\n";
//     std::cout << "Shape of Matrix M = (" << matrix_m.get_number_of_rows()
//         << ", " << matrix_m.get_number_of_columns() << ")" << std::endl;
//     std::cout << std::endl;
// }

// void demonstrate_matrix_instream()
// {
//     std::cout << "-----------------------------------------------\n";
//     std::cout << "Matrix construction from instream demonstration\n";
//     std::cout << "To: \"show that you can read in the matrix A\"\n";
//     std::cout << "-----------------------------------------------\n";

//     matrix<double> matrix_in;
//     std::cout << "Enter a matrix in the form of of a space separated list:"
//                  " {number_of_rows} {number_of_columns} {element_11} "
//                  "{element_12} ... {element_nm}" << std::endl;
//     std::cin >> matrix_in;  // e.g. for a 2D identity = 2 2 1 0 0 1

//     std::cout << "The matrix, M, you entered has the shape: ("
//         << matrix_in.get_number_of_rows() << ", "
//         << matrix_in.get_number_of_columns() << ") with elements:\n"
//         << matrix_in;

//     if (matrix_in.get_number_of_rows() == matrix_in.get_number_of_columns()) {
//         std::cout << "det(M) = " << matrix_in.determinant() << std::endl;
//         std::cout << "M^2 = \n" << matrix_in * matrix_in;
//     }

//     std::cout << std::endl;
// }

// // int main()
// // {
// //     std::cout << "-------------------\n";
// //     std::cout << "Matrices being used\n";
// //     std::cout << "-------------------" << std::endl;

// //     double a_elements[9] = {1, 2, 3, 9, 8, 7, 4, 2, 6};
// //     matrix matrix_a{3, 3, a_elements};

// //     std::cout << "Matrix A:\n" << matrix_a << "-----"<< std::endl;

// //     double b_elements[9] = {5, 5, 4, 1, 2, 3, 6, 9, 8};
// //     matrix matrix_b{3, 3, b_elements};

// //     std::cout << "Matrix B:\n" << matrix_b << "-----"<< std::endl;

// //     double c_elements[6] = {3, 4, 1, 2, 5, 6};
// //     matrix matrix_c{2, 3, c_elements};

// //     std::cout << "Matrix C:\n" << matrix_c << "-----"<< std::endl;
// //     std::cout << std::endl;

// //     demonstrate_operations(matrix_a, matrix_b, matrix_c);
// //     demonstrate_determinant(matrix_a, matrix_b);
// //     demonstrate_row_and_column_deletion(matrix_a);
// //     demonstrate_copy_constructor();
// //     demonstrate_copy_assignment();
// //     demonstrate_move_constructor();
// //     demonstrate_move_assignment();
// //     demonstrate_matrix_instream();

// //     return 0;
// // }
