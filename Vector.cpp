
#include "Vector.hpp"
#include "Quaternion.hpp"

#include "Math.h"

using std::ostream;

ostream & operator<<(ostream &os, const Vector3f &v) {
    os << '{' << v.x << ", " << v.y << ", " << v.z << '}';
}

void Vector3f::rotate(float angle, const Vector3f &axis) {
    float sinHalfA = sinf(DEG2RAD(angle / 2));
    float cosHalfA = cosf(DEG2RAD(angle / 2));

    Quaternion rot(axis.x * sinHalfA, axis.y * sinHalfA, axis.z * sinHalfA, cosHalfA);

    Quaternion conj = rot.conjugate();
    Quaternion ret = rot * (*this) * conj;
    x = ret.x;
    y = ret.y;
    z = ret.z;
}
