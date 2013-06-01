
#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector.h"

struct Quaternion {
    float x, y, z, w;
    Quaternion(float, float, float, float);

    void normalize();

    Quaternion conjugate();

    Quaternion operator*(const Quaternion &);
    Quaternion operator*(const Vector3f &);
};

#endif
