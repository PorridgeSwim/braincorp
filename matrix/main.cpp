#include "matrix.hpp"
#include <iostream>
#include <cassert>


void testMatrixMultiplication() {
    bool hasError;

    Matrix mat1(2, 4, {3, 2, 1, 5, 9, 1, 3, 0});
    Matrix mat2(3, 2, {7, 8, 9, 10, 11, 12});
    
    // test whether the invalid matrix for multiplication
    // can be recognized
    try {
        Matrix product = mat1 * mat2;

        hasError = true;
    } catch (const std::invalid_argument& err) {
        hasError = false;
    }
    assert(hasError == false);

    // test whether the calculation is correct
    // mat1 = [3, 2, 1, 5]; mat3 = [2, 9, 0]; mat1 * mat3 = [50, 42, 42]
    //        [9, 1, 3, 0]         [1, 3, 5]                [25, 96, 26]
    //                             [2, 4, 7]
    //                             [8, 1, 5]
    Matrix mat3(4, 3, {2, 9, 0, 1, 3, 5, 2, 4, 7, 8, 1, 5});
    Matrix product = mat1 * mat3;
    Matrix mat4(2, 3, {50, 42, 42, 25, 96, 26});
    assert(product.isEqualTo(mat4));

    std::cout << "(1/2) Matrix multiplication test passed!" << std::endl;
}

void testTranspose() {
    Matrix mat1(2, 3, {1, 2, 3, 4, 5, 6});
    Matrix mat2(mat1);

    // test whether twice tranpose do nothing
    mat1.transpose();
    assert(mat1.isEqualTo(mat2) == false);
    mat1.transpose();
    assert(mat1.isEqualTo(mat2) == true);

    // test whether the tranpose is correct
    // mat3 = [3, 2, 1, 5]; mat3^T = [3, 9]
    //        [9, 1, 3, 0]           [2, 1]
    //                               [1, 3]
    //                               [5, 0]
    Matrix mat3(2, 4, {3, 2, 1, 5, 9, 1, 3, 0});
    Matrix mat4(4, 2, {3, 9, 2, 1, 1, 3, 5, 0});
    assert(mat3.isEqualTo(mat4) == false);
    mat3.transpose();
    assert(mat3.isEqualTo(mat4) == true);

    std::cout << "(2/2) Matrix transpose test passed!" << std::endl;
}

int main()
{
    testMatrixMultiplication();
    testTranspose();
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}