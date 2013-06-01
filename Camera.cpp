
#include <GL/glut.h>
#include <iostream>

#include "Camera.h"
#include "Math.h"

using namespace std;

void Camera::onKeyboard(int key) {

    switch(key) {
    case GLUT_KEY_UP:
        position += (target * step); 
        break;
    case GLUT_KEY_DOWN:
        position -= (target * step);
        break;
    case GLUT_KEY_LEFT: {
        Vector3f left = target.cross(up);
        left.normalize();
        left *= step;
        position += left;
        break;
    }
    case GLUT_KEY_RIGHT: {
        Vector3f right = up.cross(target);
        right.normalize();
        right *= step;
        position += right;
        break;
    }
    }
    
}

Camera::Camera(int windowWidth, int windowHeight, const Vector3f &pos, const Vector3f &_target, const Vector3f &_up)
:windowWidth(windowWidth), windowHeight(windowHeight), position(pos), target(_target), up(_up) {
    target.normalize();
    up.normalize();

    init();
}

void Camera::init() {
    top = bottom = left = right = false;
    // the target projected onto the (x,z) plane.
    Vector3f horizTarget{target.x, 0, target.z};
    horizTarget.normalize();
    // set horizAngle based on horizTarget. asin returns a value in {90,-90} range so must modify result based on quadrant of horizTarget.
    if (horizTarget.z >= 0.0f) {
        // top half
        if (horizTarget.x >= 0.0f) {
            // topright quadrant
            horizAngle = 360 - RAD2DEG(asin(horizTarget.z));
        }
        else {
            // topleft quadrant
            horizAngle = 180 + RAD2DEG(asin(horizTarget.z));
        }
    }
    else {
        // bottom half
        if (horizTarget.x >= 0.0f) {
            // bottomright quadrant
            horizAngle = RAD2DEG(asin(-horizTarget.z));
        }
        else {
            // bottomleft quadrant
            // could also be 90 + ...
            horizAngle = 90 + RAD2DEG(asin(-horizTarget.z));
        }
    }
    vertAngle = -RAD2DEG(asin(target.y));
    mouseX = windowWidth / 2;
    mouseY = windowHeight / 2;
    glutWarpPointer(mouseX, mouseY);
}

void Camera::onMouse(int x, int y) {
    const int deltaX = x - mouseX;
    const int deltaY = y - mouseY;

    cout << "deltaX = " << deltaX << '\n';
    cout << "deltaY = " << deltaY << '\n';
    cout << "horizAngle = " << horizAngle << '\n';
    cout << "vertAngle = " << vertAngle << '\n';

    mouseX = x;
    mouseY = y;

    horizAngle += (float) deltaX / MOUSE_SCALE;
    vertAngle += (float) deltaY / MOUSE_SCALE;

    if (deltaX == 0) {
        // mouse has not moved, so if it's at the edje of the screen we'll keep moving anyway.
        if (x <= MARGIN) {
            left = true;
        }
        else if (x >= (windowWidth - MARGIN)) {
            right = true;
        }
    }
    else {
        left = right = false;
    }
    if (deltaY == 0) {
        // mouse has not moved, so if it's at the edje of the screen we'll keep moving anyway.
        if (y <= MARGIN) {
            top = true;
        }
        else if (y >= (windowHeight - MARGIN)) {
            bottom = true;
        }
    }
    else {
        top = bottom = false;
    }
    update();
}

void Camera::onRender() {
    bool shouldUpdate = false;

    // If we are on an edge, and the mouse is not moving, continue moving in that direction.
    if (left) {
        horizAngle -= 0.1f;
        shouldUpdate = true;
    }
    else if (right) {
        horizAngle += 0.1f;
        shouldUpdate = true;
    }

    if (top) {
        if (vertAngle > -90.0f) {
            vertAngle -= 0.1f;
            shouldUpdate = true;
        }
    }
    else if (bottom) {
        if (vertAngle < 90.0f) {
            vertAngle += 0.1f;
            shouldUpdate = true;
        }
    }

    if (shouldUpdate) {
        update();
    }
}

void Camera::update() {
    Vector3f vertAxis(0.0f, 1.0f, 0.0f);

    // Rotate view vector by horizontal angle around vertical axis.
    Vector3f view(1.0f, 0.0f, 0.0f);
    view.rotate(horizAngle, vertAxis);
    view.normalize();

    Vector3f horizAxis = vertAxis.cross(view);
    horizAxis.normalize();
    view.rotate(vertAngle, horizAxis);

    target = view;
    target.normalize();

    up = target.cross(horizAxis);
    up.normalize();
    cout << "up: " << up << '\n';
    cout << "target: " << target << '\n';
}
