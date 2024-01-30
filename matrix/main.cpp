#include "matrix.hpp"
#include <iostream>

int main()
{
    Matrix matA(2, 3, {1, 2, 3, 4, 5, 6});
    Matrix matB(2, 3, {7, 8, 9, 10, 11, 12});

    // Display the original matrices
    std::cout << "Matrix A:" << std::endl;
    for (size_t i = 0; i < matA.getRowSize(); ++i) {
        for (size_t j = 0; j < matA.getColSize(); ++j) {
            std::cout << matA(i, j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Matrix B:" << std::endl;
    for (size_t i = 0; i < matB.getRowSize(); ++i) {
        for (size_t j = 0; j < matB.getColSize(); ++j) {
            std::cout << matB(i, j) << " ";
        }
        std::cout << std::endl;
    }
    Matrix sum = matA - matB;
    std::cout << "Transposed Matrix A:" << std::endl;
    for (size_t i = 0; i < sum.getRowSize(); ++i) {
        for (size_t j = 0; j < sum.getColSize(); ++j) {
            std::cout << sum(i, j) << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}