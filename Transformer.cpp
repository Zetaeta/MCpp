
#include <math.h>

#include "Transformer.h"
#include "Vector.h"

#include "Math.h"

using std::cout;

Transformer::Transformer() {
//    std::cout << result << '\n';
}

void Transformer::translate(float x, float y, float z) {
    translation = {
        1.0f, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    };
    recalculate();
}

void Transformer::scale(float x, float y, float z) {
    scale_ = {
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    };
    recalculate();
}

void Transformer::rotate(float x, float y, float z) {

    Matrix4f rotX = {
        1.0f, 0, 0, 0,
        0, cosf(x), -sinf(x), 0,
        0, sinf(x), cosf(x), 0,
        0, 0, 0, 1
    };

    Matrix4f rotY = {
        cosf(y), 0, -sinf(y), 0,
        0, 1, 0, 0,
        sinf(x), 0, cosf(x), 0,
        0, 0, 0, 1
    };

    Matrix4f rotZ = {
        cosf(z), -sinf(z), 0, 0,
        sinf(z), cosf(z), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    rotation = rotZ * rotY * rotX;
    recalculate();
}

void Transformer::setView(float fov, float aspect, float nearZ, float farZ) {
    float rangeZ = nearZ - farZ;
    float tanHalfFov = tanf(DEG2RAD(fov / 2.0f));
    perspective = {
        1.0f / (aspect * tanHalfFov), 0, 0, 0,
        0, 1.0f / tanHalfFov, 0, 0,
        0, 0, (nearZ - farZ) / rangeZ, (2 * farZ * nearZ) / rangeZ,
        0, 0, 1, 0
    };
    recalculate();
}

void Transformer::cameraTranslate(Vector3f pos) {
    cameraTrans = {
        1.0f, 0, 0, -pos.x,
        0, 1, 0, -pos.y,
        0, 0, 1, -pos.z,
        0, 0, 0, 1
    };
    recalculate();
}

void Transformer::cameraAngle(Vector3f target, Vector3f up) {
    Vector3f n = target.normalize();
    Vector3f v = up.normalize();
//    cout << "up.normalize(): " << v << '\n';
    Vector3f u = v.cross(n);
    v = n.cross(u);
//    cout << "u: " << u << '\n';
//    cout << "v: " << v << '\n';
//    cout << "n: " << n << '\n';

    cameraAngle_ = {
        u.x, u.y, u.z, 0,
        v.x, v.y, v.z, 0,
        n.x, n.y, n.z, 0,
        0, 0, 0, 1
    };
    recalculate();
}

void Transformer::recalculate() {
    result = perspective * cameraAngle_ * cameraTrans * translation * rotation * scale_;
}

const Matrix4f & Transformer::get() {
    return result;
}

