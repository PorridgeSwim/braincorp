#include "matrix.hpp"
#include <stdexcept>

using std::vector;

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

size_t Matrix::getRowSize() const
{
    return this->m_rowSize;
}

size_t Matrix::getColSize() const
{
    return this->m_colSize;
}

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
            this->m_matrix[i][j] = i_vector[i * rowSize + j];
        }
    }
}

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
