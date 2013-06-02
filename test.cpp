
#include <iostream>
#include "Vector.hpp"

using std::cout;

int main() {
    Vector3f view(1.0f, 0.0f, 0.0f);
    view.rotate(90, {0.0f, 1.0f, 0.0f});
    cout << view;
}
