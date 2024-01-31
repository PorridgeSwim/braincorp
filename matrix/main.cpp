#include "matrix.hpp"
#include <iostream>

int main()
{
    Matrix matA(2, 3, {1, 2, 3, 4, 5, 6});
    Matrix matB(2, 3, {7, 8, 9, 10, 11, 12});

    // Display the original matrices
    std::cout << "Matrix A:" << std::endl;
    for (size_t i = 0; i < matA.getRowSize(); i++) {
        for (size_t j = 0; j < matA.getColSize(); j++) {
            std::cout << matA(i, j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Matrix B:" << std::endl;
    matB.transpose();
    for (size_t i = 0; i < matB.getRowSize(); i++) {
        for (size_t j = 0; j < matB.getColSize(); j++) {
            std::cout << matB(i, j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "A * B:" << std::endl;
    Matrix mat = matA * matB;
    for (size_t i = 0; i < mat.getRowSize(); i++) {
        for (size_t j = 0; j < mat.getColSize(); j++) {
            std::cout << mat(i, j) << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}