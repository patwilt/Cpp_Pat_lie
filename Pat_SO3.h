#pragma once
#include "Eigen/Dense"

class Pat_SO3 {
public:
    Pat_SO3(Eigen::Matrix3f R = Eigen::Matrix3f::Identity());
    static bool is_SO3(const Eigen::Matrix3f& R);
    static Pat_SO3 from_matrix(const Eigen::Matrix3f& R);
    static Eigen::Matrix3f skew(const Eigen::Vector3f& v);
    static Eigen::Matrix3f matrix_exponential(const Eigen::Matrix3f& M);
    friend std::ostream& operator<<(std::ostream& os, const Pat_SO3& obj);
    Eigen::Matrix3f get_rot() const { return _rot; }
private:
    Eigen::Matrix3f _rot;
};
