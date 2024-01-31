#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>

using std::vector;

class Matrix {
public:
    // Constructors
    Matrix(size_t rowSize, size_t colSize, double initial);
    Matrix(size_t rowSize, size_t colSize, const vector<double>& i_vector);

    // Operator for matrix operations
    Matrix operator+(const Matrix& rhs) const;
    Matrix operator-(const Matrix& rhs) const;
    Matrix operator*(const Matrix& rhs) const;

    // Non-const element access
    double& operator()(size_t rowId, size_t colId);
    const double& operator()(size_t rowId, size_t colId) const;

    // Transpose
    void transpose();

    // Utility functions
    bool isEqualTo(const Matrix& other) const;
    size_t getRowSize() const;
    size_t getColSize() const;

private:
    size_t m_rowSize, m_colSize;
    // bool m_transposed;
    vector<vector<double>> m_matrix;
};


#endif