
#ifndef CAMERA_H
#define CAMERA_H

#include "Vector.h"

#define MOUSE_SCALE 20.0f
#define MARGIN 10

class Camera {
public:

    Camera(int windowWidth, int windowHeight, const Vector3f &pos = {0.0f, 0.0f, 0.0f}, const Vector3f &target = {0.0f, 0.0f, 1.0f}, const Vector3f &up = {0.0f, 1.0f, 0.0f});
//    Camera()
//    :position(0, 0, 0), target(0, 0, 1), up(0, 1, 0) {}

    void onKeyboard(int keycode);
    void onMouse(int, int);
    void onRender();

    Vector3f getPos() const {
        return position;
    }
    Vector3f getTarget() const {
        return target;
    }
    Vector3f getUp() const {
        return up;
    }
private:
    void init();
    void update();

    int windowWidth, windowHeight;

    // mouse is at top, bottom, left or right area of screen.
    bool top, bottom, left, right;

    Vector3f position, target, up;
    float horizAngle;
    float vertAngle;

    int mouseX, mouseY;
    const float step = 0.1f;
};

#endif
