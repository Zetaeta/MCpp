
#include "Quaternion.hpp"

#include "Math.h"

Quaternion::Quaternion(float x, float y, float z, float w)
:x(x), y(y), z(z), w(w) {
    
}

void Quaternion::normalize() {
    float length = sqrtf(x*x + y*y + z*z + w*w);
    x /= length;
    y /= length;
    z /= length;
    w /= length;
}

Quaternion Quaternion::conjugate() {
    return Quaternion(-x, -y, -z, w);
}

Quaternion Quaternion::operator*(const Quaternion &o) {
    float _w = (w * o.w) - (x * o.x) - (y * o.y) - (z * o.z);
    float _x = (x * o.w) + (w * o.x) + (y * o.z) - (z * o.y);
    float _y = (y * o.w) + (w * o.y) + (z * o.x) - (x * o.z);
    float _z = (z * o.w) + (w * o.z) + (x * o.y) - (y * o.x);

    return Quaternion(_x, _y, _z, _w);
}

Quaternion Quaternion::operator*(const Vector3f &o) {
    float _w = - (x * o.x) - (y * o.y) - (z * o.z);
    float _x =   (w * o.x) + (y * o.z) - (z * o.y);
    float _y =   (w * o.y) + (z * o.x) - (x * o.z);
    float _z =   (w * o.z) + (x * o.y) - (y * o.x);

    return Quaternion(_x, _y, _z, _w);
}
