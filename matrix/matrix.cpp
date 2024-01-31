#include "matrix.hpp"
#include <stdexcept>

using std::vector;

// initialize the matrix with value initial for all elements
//
Matrix::Matrix(size_t rowSize, size_t colSize, double initial)
{
    size_t i;

    // error checking
    if (rowSize <= 0) {
        throw std::invalid_argument("Constructor: Row size must be greater than 0!!!");
    }
    if (colSize <= 0) {
        throw std::invalid_argument("Constructor: Column size must be greater than 0!!!");
    }

    // initialization
    this->m_rowSize = rowSize;
    this->m_colSize = colSize;
    this->m_matrix.resize(rowSize);
    for (i = 0; i < rowSize; i++) {
        this->m_matrix[i].resize(colSize, initial);
    }
}

// initizalize matrix with the given vector that has length rowSize * colSize
//
Matrix::Matrix(size_t rowSize, size_t colSize, const vector<double>& i_vector)
{
    size_t i, j;

    // error checking
    if (rowSize <= 0) {
        throw std::invalid_argument("Constructor: Row size must be greater than 0!!!");
    }
    if (colSize <= 0) {
        throw std::invalid_argument("Constructor: Column size must be greater than 0!!!");
    }
    if (rowSize * colSize != i_vector.size()) {
        throw std::invalid_argument("Constructor: Input vector size is inconsistent with given row and column size!!!");
    }

    //initizalization
    this->m_rowSize = rowSize;
    this->m_colSize = colSize;
    this->m_matrix.resize(rowSize);
    for (i = 0; i < rowSize; i++) {
        this->m_matrix[i].resize(colSize);
        for (j = 0; j < colSize; j++) {
            this->m_matrix[i][j] = i_vector[i * colSize + j];
        }
    }
}

// initizalize matrix with the copy of another matrix
//
Matrix::Matrix(const Matrix& other)
{
    size_t i, j;

    //initizalization
    this->m_rowSize = other.getRowSize();
    this->m_colSize = other.getColSize();
    this->m_matrix.resize(this->m_rowSize);
    for (i = 0; i < this->m_rowSize; i++) {
        this->m_matrix[i].resize(this->m_colSize);
        for (j = 0; j < this->m_colSize; j++) {
            this->m_matrix[i][j] = other(i,j);
        }
    }
}

// non-const quick access of matrix element
//
double& Matrix::operator()(size_t rowId, size_t colId)
{
    // error checking
    if (rowId >= this->m_rowSize) {
        throw std::invalid_argument("Quick access: Row index out of range!!!");
    }
    if (colId >= this->m_colSize) {
        throw std::invalid_argument("Quick access: Column index out of range!!!");
    }

    return this->m_matrix[rowId][colId];
}

// const quick access of matrix element
//
const double& Matrix::operator()(size_t rowId, size_t colId) const
{
    // error checking
    if (rowId >= this->m_rowSize) {
        throw std::invalid_argument("Quick access: Row index out of range!!!");
    }
    if (colId >= this->m_colSize) {
        throw std::invalid_argument("Quick access: Column index out of range!!!");
    }

    return this->m_matrix[rowId][colId];
}

// get the number of rows
//
size_t Matrix::getRowSize() const
{
    return this->m_rowSize;
}

// get the number of columns
//
size_t Matrix::getColSize() const
{
    return this->m_colSize;
}

// return whether the two matrices are equal
//
bool Matrix::isEqualTo(const Matrix& rhs) const
{
    size_t leftRowSize, rightRowSize, leftColSize, rightColSize, i, j;

    // return false if row sizes are unequal
    leftRowSize = this->m_rowSize;
    rightRowSize = rhs.getRowSize();
    if (leftRowSize != rightRowSize) {
        return false;
    }

    // return false if column sizes are unequal
    leftColSize = this->m_colSize;
    rightColSize = rhs.getColSize();
    if (leftColSize != rightColSize) {
        return false;
    }

    // return false if two elements in the same place are unequal
    for (i = 0; i < leftRowSize; i++) {
        for (j = 0; j < leftColSize; j++) {
            if (this->m_matrix[i][j] != rhs(i,j)) {
                return false;
            }
        }
    }

    // else, return true
    return true;
}

// print the matrix
void Matrix::print() const
{
    size_t i, j;
    
    std::cout << "Matrix: " << std::endl;
    for (i = 0; i < this->m_rowSize; i++) {
        std::cout << "[";
        for (j = 0; j < this->m_colSize; j++) {
            std::cout << m_matrix[i][j] << " ";
        }
        std::cout << "]" << std::endl;
    }
}



// implement matrix addition
//
Matrix Matrix::operator+(const Matrix& rhs) const
{
    size_t leftRowSize, rightRowSize, leftColSize, rightColSize, i, j;

    // error checking
    leftRowSize = this->m_rowSize;
    rightRowSize = rhs.getRowSize();
    if (leftRowSize != rightRowSize) {
        throw std::invalid_argument("Matrix Addition: Different row sizes!!!");
    }
    leftColSize = this->m_colSize;
    rightColSize = rhs.getColSize();
    if (leftColSize != rightColSize) {
        throw std::invalid_argument("Matrix Addition: Different column sizes!!!");
    }

    // implement addition
    Matrix sum(leftRowSize, leftColSize, 0.0);
    for (i = 0; i < leftRowSize; i++) {
        for (j = 0; j < leftColSize; j++) {
            sum(i,j) = this->m_matrix[i][j] + rhs(i,j);
        }
    }
    return sum;
}

// implement matrix substraction
//
Matrix Matrix::operator-(const Matrix& rhs) const
{
    size_t leftRowSize, rightRowSize, leftColSize, rightColSize, i, j;

    // error checking
    leftRowSize = this->m_rowSize;
    rightRowSize = rhs.getRowSize();
    if (leftRowSize != rightRowSize) {
        throw std::invalid_argument("Matrix substraction: Different row sizes!!!");
    }
    leftColSize = this->m_colSize;
    rightColSize = rhs.getColSize();
    if (leftColSize != rightColSize) {
        throw std::invalid_argument("Matrix substraction: Different column sizes!!!");
    }

    // implement substraction
    Matrix diff(leftRowSize, leftColSize, 0.0);
    for (i = 0; i < leftRowSize; i++) {
        for (j = 0; j < leftColSize; j++) {
            diff(i,j) = this->m_matrix[i][j] - rhs(i,j);
        }
    }
    return diff;
}

// implement matrix multiplication
//
Matrix Matrix::operator*(const Matrix& rhs) const
{
    size_t leftRowSize, rightRowSize, leftColSize, rightColSize, i, j, k;

    // error checking
    leftRowSize = this->m_rowSize;
    leftColSize = this->m_colSize;
    rightRowSize = rhs.getRowSize();
    rightColSize = rhs.getColSize();
    if (leftColSize != rightRowSize) {
        throw std::invalid_argument("Matrix multiplication: The sizes of two matrices are unmatched!!!");
    }

    // implement multiplication
    Matrix product(leftRowSize, rightColSize, 0.0);
    for (i = 0; i < leftRowSize; i++) {
        for (j = 0; j < rightColSize; j++) {
            for (k = 0; k < leftColSize; k ++) {
                product(i,j) += this->m_matrix[i][k] * rhs(k,j);
            }
        }
    }
    return product;
}

// implement matrix transpose
//
void Matrix::transpose()
{
    vector<vector<double>> newMatrix;
    size_t i, j, temp;

    // get the transposed matrix
    newMatrix.resize(this->m_colSize);
    for (i = 0; i < this->m_colSize; i++) {
        newMatrix[i].resize(this->m_rowSize);
        for (j = 0; j < this->m_rowSize; j++) {
            newMatrix[i][j] = this->m_matrix[j][i];
        }
    }

    // replace the old matrix by the transposed one
    this->m_matrix = newMatrix;
    temp = this->m_colSize;
    this->m_colSize = this->m_rowSize;
    this->m_rowSize = temp;
}