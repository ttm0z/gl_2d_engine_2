// Renderer.hpp
#pragma once

#include <GL/glew.h>
#include "Window.hpp"

class Renderer {
public:
    Renderer(int sWidth, int sHeight, int tWidth, int tHeight);
    ~Renderer();
    
    void init();
    
    void render();

    GLuint getShaderProgram();

    void setPositionsBuffer();

    void renderTilemap(float cameraX, float cameraY);

    void renderTile(int startX, int startY);

    static const GLfloat vertexBufferData[];

    GLsizei vertexCount;

    void setShaderProgram(GLuint programID);

private:
    GLuint programID;
    GLuint vao_ID;
    GLuint vbo_ID;
    int screenWidth;
    int screenHeight;
    int tileWidth;
    int tileHeight;
};