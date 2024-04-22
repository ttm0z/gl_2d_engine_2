// Renderer.hpp
#pragma once

#include <GL/glew.h>
#include <glm.hpp>
#include "Window.hpp"



class Renderer {
public:
    Renderer(float sWidth, float sHeight, float tWidth, float tHeight);
    ~Renderer();
    
    void init();
    
    void render();

    GLuint getShaderProgram();

    void setPositionsBuffer();

    void renderTilemap(float cameraX, float cameraY, std::vector<std::vector<int>> worldMap);

    void renderTile(int startX, int startY, int tileValue);

    static const GLfloat vertexBufferData[];

    GLsizei vertexCount;

    void setShaderProgram(GLuint programID);

private:
    GLuint programID;
    GLuint vao_ID;
    GLuint vbo_ID;
    GLuint tileVAO;
    GLuint tileVBO;

    int screenWidth;
    int screenHeight;
    int tileWidth;
    int tileHeight;
};