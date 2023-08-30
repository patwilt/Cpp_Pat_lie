#include "Pat_SO3.h"
#include <iostream>
#include <cassert>

//Test if SO3
void test_is_SO3() {
    Eigen::Matrix3f R;
    R << 1, 0, 0,
         0, 1, 0,
         0, 0, 1;
    assert(Pat_SO3::is_SO3(R) == true);
}

//test from matrix 
void test_from_matrix() {
    Eigen::Matrix3f R;
    R << 1, 0, 0,
         0, 1, 0,
         0, 0, 1;

    Pat_SO3 obj = Pat_SO3::from_matrix(R);
    assert(obj.get_rot() == R);

}

//test skew
void test_skew(){
    Eigen::Vector3f v;
    Eigen::Matrix3f v_skew;
    v << 1, 2, 3;
    //skew symmetric of v
    v_skew << 0, -3, 2,
              3, 0, -1,
              -2, 1, 0;

    assert(Pat_SO3::skew(v) == v_skew);
}


int main() {

    // Test is_SO3
    test_is_SO3();

    //test from matrix
    test_from_matrix();

    //test skew 
    test_skew();

    // Initialize a 3x3 identity matrix
    Eigen::Matrix3f M;
    M << 0, -1, 0,
         1, 0, 0,
         0, 0, 0;


    // Calculate the matrix exponential using the Pat_SO3 class's static method
    Eigen::Matrix3f expR = Pat_SO3::matrix_exponential(M);

    // Output the result
    std::cout << "Matrix Exponential of Identity:\n" << expR << std::endl;

    return 0;
}

