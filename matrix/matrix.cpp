#include "matrix.hpp"

using namespace std;

Matrix::Matrix(size_t rowSize, size_t colSize, double initial) {
    m_rowSize = rowSize;
    m_colSize = colSize;
    m_matrix.resize(rowSize);
    for (size_t i = 0; i < rowSize; i++) {
        m_matrix[i].resize(colSize, initial);
    }
}