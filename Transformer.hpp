
#ifndef TRANSFORMER_HPP
#define TRANSFORMER_HPP

#include "Matrix.hpp"
#include "Camera.hpp"

class Vector3f;

class Transformer {
public:
    Transformer();

    void translate(float x, float y, float z);
    void scale(float x, float y, float z);
    void rotate(float x, float y, float z);

    void cameraTranslate(Vector3f);
    void cameraAngle(Vector3f target, Vector3f up);

    void setView(float fov, float aspect, float nearZ, float farZ);

    void setCamera(Camera &camera) {
        cameraTranslate(camera.getPos());
        cameraAngle(camera.getTarget(), camera.getUp());
        setView(camera.getFov(), camera.getAspectRatio(), camera.getNearZ(), camera.getFarZ());
    }

    const Matrix4f & get();

private:
    void recalculate();
    Matrix4f translation;
    Matrix4f scale_;
    Matrix4f rotation;
    Matrix4f perspective;

    Matrix4f cameraTrans;
    Matrix4f cameraAngle_;

    Matrix4f result;

    int fov;
};

#endif
