
#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "Vector.hpp"

struct Quaternion {
    float x, y, z, w;
    Quaternion(float, float, float, float);

    void normalize();

    Quaternion conjugate();

    Quaternion operator*(const Quaternion &);
    Quaternion operator*(const Vector3f &);
};

#endif
