
#include "Matrix.hpp"

using std::cout;

Matrix4f::Matrix4f() {
    // identity matrix.
    memset(m, 0, sizeof(m));
    for (int i=0; i<4; ++i) {
        m[i][i] = 1;
    }
}

Matrix4f::Matrix4f(const std::initializer_list<float> &l) {
    int i = 0;
    for (float v : l) {
        m[i / 4][i % 4] = v;
        ++i;
    }
}

Matrix4f & Matrix4f::operator=(const Matrix4f &other) {
    memcpy(m, other.m, sizeof(m));
    return *this;
}

Matrix4f & Matrix4f::operator=(const std::initializer_list<float> &l) {
    *this = Matrix4f(l);
    return *this;
}

std::ostream & operator<<(std::ostream &os, Matrix4f m) {
    os << '{';
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            os << m.m[i][j];
            if (i * j != 9) // i and j are both 3.
                os << ", ";
        }
        if (i != 3) // last iteration
            os << '\n';
    }
    os << '}';
}
