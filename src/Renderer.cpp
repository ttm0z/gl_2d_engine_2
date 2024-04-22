#include "Renderer.hpp"
#include "shader.hpp"
#include <iostream>
#include "LoadShaderGeo.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


const GLfloat Renderer::vertexBufferData[] = { 
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
};

// clip space vertex coordinates and texture coordinates
// for geometry shader
const GLfloat vertexTextureBufferData[]{
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Vertex 1: Bottom-left
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Bottom-right
     0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // Vertex 3: Top-right
    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // Vertex 4: Top-left
};



Renderer::Renderer(float sWidth, float sHeight, float tWidth, float tHeight) : 
    vao_ID(0), vbo_ID(0), tileVAO(0), tileVBO(0), screenWidth(sWidth), 
    screenHeight(sHeight), tileWidth(tWidth), tileHeight(tHeight)
    {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }

    vertexCount = sizeof(vertexBufferData) / (6 * sizeof(GLfloat));
    vertexTextureCount = sizeof(vertexTextureBufferData) / (5 * sizeof(GLfloat));
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    //create and set the shader program
    GLuint program = LoadShaders( "../shaders/SimpleVertexShader.vertexshader", "../shaders/SimpleFragmentShader.fragmentshader" );
    //setShaderProgram(program);
    
    GLuint GeometryShaderProgram = LoadShadersWithGeo( "../shaders/GeoVertexShader.glsl", "../shaders/GeometryShader.glsl", "../shaders/GeoFragmentShader.glsl");
    setShaderProgram(GeometryShaderProgram);

    setPositionsBuffer();
    
    // init projection matrix
    projectionMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f);
    
    // set projectionMatrix uniform
    // Set the projection matrix uniform in the shader
    GLuint projectionMatrixID = glGetUniformLocation(programID, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &projectionMatrix[0][0]);

    // init view matrix
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    
    // set viewMatrix uniform
    GLuint viewMatrixID = glGetUniformLocation(programID, "viewMatrix");
    glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);


    // bind grass and water textures (tilemap test)
    GLuint grassTextureID = loadTexture("assets/grass.png");
    GLuint waterTextureID = loadTexture("assets/water.png");
}


Renderer::~Renderer() {
    glDeleteVertexArrays(1, &vao_ID);
    glDeleteBuffers(1, &vbo_ID);
}

void Renderer::setPositionsBuffer(){
    GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
}


GLuint Renderer::loadTexture(const std::string& filename){
    int width, height, numChannels;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &numChannels, 0);
     if (!data) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return 0;
    }
    GLuint textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = (numChannels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;


}


void Renderer::init(){
// Generate and bind Vertex Array Object (VAO)
glGenVertexArrays(1, &tileVAO);
glBindVertexArray(tileVAO);

// Generate and bind Vertex Buffer Object (VBO)
glGenBuffers(1, &tileVBO);
glBindBuffer(GL_ARRAY_BUFFER, tileVBO);

// Define the layout of the vertex data
// Position attribute (3 floats per vertex, starting from the beginning of the data)
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
glEnableVertexAttribArray(0);

// Texture coordinate attribute (2 floats per vertex, starting after the position data)
glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
glEnableVertexAttribArray(1);

// Copy vertex data into the buffer
glBufferData(GL_ARRAY_BUFFER, sizeof(vertexTextureBufferData), vertexTextureBufferData, GL_STATIC_DRAW);

// Unbind VAO 
glBindVertexArray(0);

    
}

void Renderer::setShaderProgram(GLuint programID){
    glUseProgram(programID);
}

GLuint Renderer::getShaderProgram(){
    return programID;
}

void Renderer::renderTilemap(float cameraX, float cameraY, std::vector<std::vector<int>> worldMap){
    int startTileX = (int)(cameraX / tileWidth);
    int startTileY = (int)(cameraY / tileHeight);
    int endTileX = startTileX + (screenWidth / tileWidth) + 1;
    int endTileY = startTileY + (screenHeight / tileHeight) + 1;

    // render the visible tiles within camera boundaries
    for(int y = 0; y < screenHeight / 5; y++) {
        for(int x = 0; x < screenWidth / 5; x++) {
            float tilePosX = x * tileWidth;
            float tilePosY = y * tileHeight;
            //render tile at ()
            //std::cout << "world map tile" << ": "<< worldMap[x][y] << std::endl;
            //std::cout << "tileposx" << ": "<< tilePosX << std::endl;
            //std::cout << "tileposy" << ": "<<tilePosY << std::endl;
            //std::cout << "Tile height" << ": "<<tileWidth << std::endl;
            //std::cout << "Tile width" << ": "<<tileHeight << std::endl;

            renderTile(tilePosX, tilePosY, worldMap[x][y]);
        }
    }
}

void Renderer::renderTile(float startX, float startY, int tileValue) {
    
    // set the color - temporary
    glm::vec3 color;
    if (tileValue == 0) {
        // Blue color
        color = glm::vec3(0.0f, 0.0f, 1.0f); // Blue
    } else {
        // Green color
        color = glm::vec3(0.0f, 1.0f, 0.0f); // Green
    }

    
    float tileData[] = {
        startX, startY, 0.0f, color.r, color.g, color.b,
        startX + tileWidth, startY, 0.0f, color.r, color.g, color.b,
        startX + tileWidth, startY + tileHeight, 0.0f, color.r, color.g, color.b,
        startX, startY + tileHeight, 0.0f, color.r, color.g, color.b
    };

    // Bind VAO and VBO
    glBindVertexArray(tileVAO);
    glBindBuffer(GL_ARRAY_BUFFER, tileVBO);

    // Load buffer data (both position and color)
    glBufferData(GL_ARRAY_BUFFER, sizeof(tileData), tileData, GL_STATIC_DRAW);

    // Set attribute pointers for both position and color
    // Position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Color attribute (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Render tile
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 1);
    glBindVertexArray(1);
}


// render the red triangle
void Renderer::render() {
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rendering logic goes here
    // A Simple Example: draw a triangle

    glBindVertexArray(vao_ID);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ID);

    // Update vertex buffer data
    glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(GLfloat), vertexBufferData, GL_STATIC_DRAW);

    // Draw the vertices
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}