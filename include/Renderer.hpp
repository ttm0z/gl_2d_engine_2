// Renderer.hpp
#pragma once

#include <GL/glew.h>
#include "Window.hpp"

class Renderer {
public:
    Renderer();
    ~Renderer();
    
    void init();
    
    void render();

    GLuint getShaderProgram();

    void setPositionsBuffer();

    static const GLfloat vertexBufferData[];

    GLsizei vertexCount;

    void setShaderProgram(GLuint programID);

private:
    GLuint programID;
    GLuint vao_ID;
    GLuint vbo_ID;
};