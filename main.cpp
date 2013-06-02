
#include <string.h>
#include <assert.h>
#include <math.h>

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Matrix.hpp"
#include "Transformer.hpp"
#include "Vector.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "glvars.h"
#include "Cube.hpp"


#define WIDTH  1920
#define HEIGHT 1080

using std::cerr;
using std::cout;









const char *vertexShader = "\
#version 330\n\
layout (location = 0) in vec3 position;\n\
layout (location = 1) in vec2 texCoord;\n\
out vec2 texCoord0;\n\
uniform mat4 transformation;\n\
\n\
void main() {\n\
    gl_Position = transformation * vec4(position, 1.0);\n\
    texCoord0 = texCoord;\n\
}";

const char *fragmentShader = "\
#version 330\n\
out vec4 FragColor;\n\
in vec2 texCoord0;\n\
uniform sampler2D glslSampler;\n\
void main() {\n\
    FragColor = texture2D(glslSampler, texCoord0.xy);\n\
}";

//GLuint vbo, ibo;
Texture *texture;

Camera *camera;
Cube *cube, *cube2;

void render() {

    camera->onRender();

    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    Transformer &t = cube->getTransformer();
    Transformer &t2 = cube2->getTransformer();

    static float rot = 0;
    rot += 0.01;

    float transf = sinf(rot);
//    t.translate(0, 0, 5);
//    t2.translate(1, 0.1, 5);
//    t.cameraTranslate(camera->getPos());
//    t.cameraAngle(camera->getTarget(), camera->getUp());

    cube->setCamera(*camera);
    cube2->setCamera(*camera);
    cube->draw();
    cube2->draw();
/*
    glUniformMatrix4fv(glslTransformation, 1, GL_TRUE, (const GLfloat *) &t.get());

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const GLvoid*>(12));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    texture->bind(GL_TEXTURE0);


    glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
*/

    glutSwapBuffers();

    int i = glGetError();
    if (i) cout << i << '\n';

//    cout << glGetError() << '\n';
}

void initWorld() {
    camera->setView(30.0f, 1.0, 100);
    cube->setCoords(0, 0, 5);
    cube2->setCoords(2, 1.0, 5);
}

void createBuffers() {
    
/*
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
*/
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}


void addShader(GLuint program, const char *shader, GLenum shaderType) {
    GLuint shaderObj = glCreateShader(shaderType);
    if (shaderObj == 0) {
        cerr << "Error creating shader type " << shaderType << '\n';
        exit(1);
    }

    const GLchar *shaders[1] = { shader };
    GLint lengths[1] = { strlen(shader) };
    glShaderSource(shaderObj, 1, shaders, lengths);
    glCompileShader(shaderObj);
    GLint success;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar info[1024];
        glGetShaderInfoLog(shaderObj, 1024, NULL, info);
        cerr << "Error compiling shader type " << shaderType << ": " << info << '\n';
        exit(1);
    }
    glAttachShader(shaderProgram, shaderObj);
}


void addShaders() {
    shaderProgram = glCreateProgram();
    if (!shaderProgram) {
        cerr << "Error creating shader program\n";
        exit(1);
    }
    addShader(shaderProgram, vertexShader, GL_VERTEX_SHADER);
    addShader(shaderProgram, fragmentShader, GL_FRAGMENT_SHADER);

    GLint success = 0;
    GLchar info[1024];
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, sizeof(info), NULL, info);
        cerr << "Error linking shader program: " << info << '\n';
        exit(1);
    }
    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, sizeof(info), NULL, info);
        cerr << "Invalid shader program: " << info << '\n';
        exit(1);
    }

    glUseProgram(shaderProgram);

    glslTransformation = glGetUniformLocation(shaderProgram, "transformation");
    glslSampler = glGetUniformLocation(shaderProgram, "glslSampler");
}



int main(int argc, char **argv) {

    Matrix4f m = {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };

    Matrix4f identity = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    cout << (m * identity) << '\n';

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(50, 50);

    glutCreateWindow("OpenGL");
//    glutGameModeString("2560x1440@32");
//    glutEnterGameMode();
    
    glutDisplayFunc(&render);
    glutIdleFunc(&render);
    glutSpecialFunc([] (int key, int x, int y) {
        camera->onKeyboard(key);
    });

    glutKeyboardFunc([] (unsigned char key, int x, int y) {
        if (key == 'q') exit(0);
    });
    glutPassiveMotionFunc([] (int x, int y) {
        camera->onMouse(x, y);
    });

    camera = new Camera(WIDTH, HEIGHT);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        cout << "Failed to initialise GLEW: " << glewGetErrorString(err);
        exit(1);
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    createBuffers();
    addShaders();

    glUniform1i(glslSampler, 0);

    texture = new Texture(GL_TEXTURE_2D, "stone.png");
    if (!texture->load()) {
        cout << "Failed loading\n";
        return 1;
    }
    cube = new Cube(texture);
    cube2 = new Cube(texture);

    initWorld();

    glutMainLoop();
}
