
#ifndef MATRIX_H
#define MATRIX_H

#include <string.h>

#include <initializer_list>
#include <iostream>

class Matrix4f {
public:
    Matrix4f();

    Matrix4f(const std::initializer_list<float> &l);

    Matrix4f & operator=(const std::initializer_list<float> &l);

    Matrix4f & operator=(const Matrix4f &o);

    float m[4][4];

    inline float & operator()(int i, int j) {
        return m[i][j];
    }

    inline const float & operator()(int i, int j) const {
        return m[i][j];
    }

    const Matrix4f operator*(const Matrix4f &o) const {
        Matrix4f ret;
        for (int i=0; i<4; ++i) {
            for (int j=0; j<4; ++j) {
                ret.m[i][j] =   m[i][0] * o.m[0][j] +
                                m[i][1] * o.m[1][j] +
                                m[i][2] * o.m[2][j] +
                                m[i][3] * o.m[3][j];
            }
        }
        return ret;
    }

};

std::ostream & operator<<(std::ostream &os, Matrix4f m);

#endif
