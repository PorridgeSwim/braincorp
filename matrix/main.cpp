#include "matrix.hpp"
#include <iostream>
#include <cassert>


void testMatrixMultiplication() {
    bool passed;

    Matrix mat1(2, 3, {1, 2, 3, 4, 5, 6});
    Matrix mat2(2, 3, {7, 8, 9, 10, 11, 12});
    
    try {
        Matrix product = mat1 * mat2;

        passed = true;
    } catch (const std::invalid_argument& err) {
        passed = false;
    }
    assert(passed == false);

    Matrix mat3(3, 2, {7, 8, 9, 10, 11, 12});
    Matrix product = mat1 * mat3;
    Matrix mat4(2, 2, {58, 64, 139, 154});
    assert(product.isEqualTo(mat4));

    std::cout << "Multiplication test passed." << std::endl;
}

int main()
{
    testMatrixMultiplication();
    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}