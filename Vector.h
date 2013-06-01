
#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include <assert.h>
#include <math.h>

#include <iostream>

struct Vector2f {
    float x;
    float y;

    Vector2f() {}

    Vector2f(float x, float y)
    :x(x), y(y) {}
};

class Vector3f {
public:
    float x, y, z;

    Vector3f()
    :x(0), y(0), z(0) {}

    Vector3f(float x, float y, float z)
    :x(x), y(y), z(z) {}

    Vector3f(const std::initializer_list<float> &l) {
        assert(l.size() == 3);
        auto *p = l.begin();
        x = *p++;
        y = *p++;
        z = *p++;
    }

    Vector3f operator=(const std::initializer_list<float> &l) {
        assert(l.size() == 3);
        auto *p = l.begin();
        x = *p++;
        y = *p++;
        z = *p++;
    }

    Vector3f cross(const Vector3f &o) {
        float _x = y * o.z - z * o.y;
        float _y = z * o.x - x * o.z;
        float _z = x * o.y - y * o.x;
        return Vector3f(_x, _y, _z);
    }

    Vector3f normalize() {
        float length = sqrtf(x * x + y * y + z * z);
        return Vector3f(x / length, y / length, z / length);
    }

    Vector3f & operator*=(float f) {
        x *= f;
        y *= f;
        z *= f;
    }

    Vector3f operator*(float f) {
        Vector3f o(*this);
        o *= f;
        return o;
    }

    Vector3f & operator+=(const Vector3f &o) {
        x += o.x;
        y += o.y;
        z += o.z;
    }

    Vector3f operator+(const Vector3f &o) {
        Vector3f r(*this);
        r += o;
        return r;
    }

    Vector3f & operator-=(const Vector3f &o) {
        x -= o.x;
        y -= o.y;
        z -= o.z;
    }

    Vector3f operator-(const Vector3f &o) {
        Vector3f r(*this);
        r -= o;
        return r;
    }

    void rotate(float angle, const Vector3f &axis);
};

std::ostream & operator<<(std::ostream &, const Vector3f &);

#endif
