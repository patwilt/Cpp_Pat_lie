#include "Pat_SO3.h"
#include <iostream>
#include <cmath>
#include "Eigen/Dense"

Pat_SO3::Pat_SO3(Eigen::Matrix3f R) {
    if (is_SO3(R)) {
        _rot = R;
    } else {
        _rot = Eigen::Matrix3f::Identity();
    }
}

bool Pat_SO3::is_SO3(const Eigen::Matrix3f& R) {
    return true;  // Always true for 3x3
}


Pat_SO3 Pat_SO3::from_matrix(const Eigen::Matrix3f& R) {
    if (is_SO3(R)) {
        return Pat_SO3(R);
    } else {
        throw std::invalid_argument("Not a valid SO3 matrix");
    }
}

Eigen::Matrix3f Pat_SO3::skew(const Eigen::Vector3f& v) {
    Eigen::Matrix3f skew_matrix;
    skew_matrix << 0, -v(2), v(1),
                   v(2), 0, -v(0),
                  -v(1), v(0), 0;
    return skew_matrix;
}

Eigen::Matrix3f Pat_SO3::matrix_exponential(const Eigen::Matrix3f& M) {
    Eigen::Matrix3f result;
    Eigen::Matrix3f input_matrix = M;  // Copy of input matrix to manipulate if needed
    double theta = M.norm() / std::sqrt(2);
    double A, B;

    //Check shape
    if (M.rows() == 3 && M.cols() == 3) {
        theta = M.norm() / std::sqrt(2.0);
    } else if (M.rows() == 3 && M.cols() == 1) {
        Eigen::Vector3f vec(M(0,0), M(1,0), M(2,0));  // Create a vector from the matrix
        theta = vec.norm();
        input_matrix = skew(vec); 
    }

    if (theta > 1e-6) {
        A = std::sin(theta) / theta;
        B = (1.0 - std::cos(theta)) / std::pow(theta, 2);
    } else {
        A = 1.0;
        B = 1.0 / 2.0;
    }

    Eigen::Matrix3f exponential = Eigen::Matrix3f::Identity() + A * input_matrix + B * input_matrix * input_matrix;
    return exponential;
}


std::ostream& operator<<(std::ostream& os, const Pat_SO3& obj) {
    os << obj._rot;
    return os;
}
