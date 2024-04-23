// Renderer.hpp
#pragma once

#include <GL/glew.h>
#include <gtc/matrix_transform.hpp> // For glm::ortho
#include <glm.hpp>
#include <string>
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

    void renderTile(float startX, float startY, int tileValue);

    GLuint loadTexture(const std::string& filename);


    GLsizei vertexCount;
    GLsizei vertexTextureCount;

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

    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;

};
