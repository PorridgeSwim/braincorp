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
        throw std::invalid_argument("Row size must be greater than 0!!!");
    }
    if (colSize <= 0) {
        throw std::invalid_argument("Column size must be greater than 0!!!");
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
Matrix::Matrix(size_t rowSize, size_t colSize, const vector<double>& i_vector)
{
    size_t i, j;

    // error checking
    if (rowSize <= 0) {
        throw std::invalid_argument("Row size must be greater than 0!!!");
    }
    if (colSize <= 0) {
        throw std::invalid_argument("Column size must be greater than 0!!!");
    }
    if (rowSize * colSize != i_vector.size()) {
        throw std::invalid_argument("Input vector size is inconsistent with given row and column size!!!");
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

// non-const quick access of matrix element
//
double& Matrix::operator()(size_t rowId, size_t colId)
{
    if (rowId >= this->m_rowSize) {
        throw std::invalid_argument("Row index out of range!!!");
    }
    if (colId >= this->m_colSize) {
        throw std::invalid_argument("Column index out of range!!!");
    }
    return this->m_matrix[rowId][colId];
}

// const quick access of matrix element
//
const double& Matrix::operator()(size_t rowId, size_t colId) const
{
    if (rowId >= this->m_rowSize) {
        throw std::invalid_argument("Row index out of range!!!");
    }
    if (colId >= this->m_colSize) {
        throw std::invalid_argument("Column index out of range!!!");
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

bool Matrix::isEqualTo(const Matrix& rhs) const
{
    size_t leftRowSize, rightRowSize, leftColSize, rightColSize, i, j;
    leftRowSize = this->m_rowSize;
    rightRowSize = rhs.getRowSize();
    if (leftRowSize != rightRowSize) {
        return false;
    }
    leftColSize = this->m_colSize;
    rightColSize = rhs.getColSize();
    if (leftColSize != rightColSize) {
        return false;
    }

    for (i = 0; i < leftRowSize; i++) {
        for (j = 0; j < leftColSize; j++) {
            if (this->m_matrix[i][j] != rhs(i,j)) {
                return false;
            }
        }
    }

    return true;
}



// implement matrix addition
//
Matrix Matrix::operator+(const Matrix& rhs) const
{
    size_t leftRowSize, rightRowSize, leftColSize, rightColSize, i, j;

    leftRowSize = this->m_rowSize;
    rightRowSize = rhs.getRowSize();
    if (leftRowSize != rightRowSize) {
        throw std::invalid_argument("Different row sizes!!!");
    }

    leftColSize = this->m_colSize;
    rightColSize = rhs.getColSize();
    if (leftColSize != rightColSize) {
        throw std::invalid_argument("Different column sizes!!!");
    }

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

    leftRowSize = this->m_rowSize;
    rightRowSize = rhs.getRowSize();
    if (leftRowSize != rightRowSize) {
        throw std::invalid_argument("Different row sizes!!!");
    }

    leftColSize = this->m_colSize;
    rightColSize = rhs.getColSize();
    if (leftColSize != rightColSize) {
        throw std::invalid_argument("Different column sizes!!!");
    }

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
    leftRowSize = this->m_rowSize;
    leftColSize = this->m_colSize;
    rightRowSize = rhs.getRowSize();
    rightColSize = rhs.getColSize();
    if (leftColSize != rightRowSize) {
        throw std::invalid_argument("The sizes of two matrices are unmatched!!!");
    }
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

    newMatrix.resize(this->m_colSize);
    for (i = 0; i < this->m_colSize; i++) {
        newMatrix[i].resize(this->m_rowSize);
        for (j = 0; j < this->m_rowSize; j++) {
            newMatrix[i][j] = this->m_matrix[j][i];
        }
    }
    this->m_matrix = newMatrix;
    temp = this->m_colSize;
    this->m_colSize = this->m_rowSize;
    this->m_rowSize = temp;
}