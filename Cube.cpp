
#include "Cube.hpp"
#include "glvars.h"
#include "Transformer.hpp"
#include "Texture.hpp"

Cube::Cube(Texture *texture)
:texture(texture), size(1) {
    vertices = {
        Vertex(Vec(0.5f, 0.5f, 0.5f), Vec(1,1)),  // 0
        Vertex(Vec(0.5f, 0.5f, -0.5f), Vec(0,1)),  // 1
        Vertex(Vec(0.5f, -0.5f, 0.5f), Vec(1,0)),  // 2
        Vertex(Vec(0.5f, -0.5f, -0.5f), Vec(0,0)), // 3
        Vertex(Vec(-0.5f, 0.5f, 0.5f), Vec(0,1)),  // 4
        Vertex(Vec(-0.5f, 0.5f, -0.5f), Vec(1,1)), // 5
        Vertex(Vec(-0.5f, -0.5f, 0.5f), Vec(0,0)), // 6
        Vertex(Vec(-0.5f, -0.5f, -0.5f), Vec(1,0)),// 7

        Vertex(Vec(-0.5f, 0.5f, -0.5f), Vec(0,0)), // 8: 5 with texture coordinates for top/bottom
        Vertex(Vec(-0.5f, -0.5f, -0.5f), Vec(0,1)),// 9: 7 with texture coordinates for top/bottom
    };



    indices = {
        // back & front
        0, 4, 6,
        0, 6, 2,

        1, 3, 7,
        1, 7, 5,

        // bottom & top
        2, 9, 3,
        2, 6, 9,

        0, 1, 8,
        0, 8, 4,

        // right & left
        0, 2, 3,
        0, 3, 1,

        4, 7, 6,
        4, 5, 7
    };

    createBuffers();
    update();

}

void Cube::update() {
    transformer.scale(size, size, size);
    transformer.translate(coords.x, coords.y, coords.z);
}

void Cube::createBuffers() {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void Cube::draw() {

    glUniformMatrix4fv(glslTransformation, 1, GL_TRUE, (const GLfloat *) &transformer.get());

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, reinterpret_cast<const GLvoid*>(12));

    texture->bind(GL_TEXTURE0);

    glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void Cube::setCamera(Camera &camera) {
    transformer.setCamera(camera);
}
