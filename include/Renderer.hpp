// Renderer.hpp
#pragma once

#include <GL/glew.h>
#include "Window.hpp"

class Renderer {
public:
    Renderer();
    ~Renderer();
    
    void init();
    
    void render(const GLfloat* vertexData, GLsizei vertexCount);

    GLuint getShaderProgram();

    void setShaderProgram(GLuint programID);

private:
    GLuint programID;
    GLuint vao_ID;
    GLuint vbo_ID;
};