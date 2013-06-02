
#ifndef CUBE_HPP
#define CUBE_HPP

#include <vector>

#include <GL/glew.h>

#include "Vector.hpp"
#include "Transformer.hpp"
#include "Camera.hpp"

using std::vector;

class Transformer;
class Texture;

class Cube {
public:
    Cube(Texture *texture);

    void draw();

    Transformer &getTransformer() {
        return transformer;
    }

    void setCoords(float x, float y, float z) {
        coords.x = x;
        coords.y = y;
        coords.z = z;
        update();
    }

    void setSize(float s) {
        size = s;
        update();
    }

    void setCamera(Camera &camera);

private:
    void createBuffers();
    void update();

    Texture *texture;
    Transformer transformer;
    GLuint vbo, ibo;
    vector<Vertex> vertices;
    vector<GLuint> indices;

    Vector3f coords;
    float size;

};

#endif
