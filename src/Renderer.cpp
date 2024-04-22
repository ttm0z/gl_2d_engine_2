#include "Renderer.hpp"
#include "shader.hpp"
#include <iostream>

const GLfloat Renderer::vertexBufferData[] = { 
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
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

    vertexCount = sizeof(vertexBufferData) / (3 * sizeof(GLfloat));
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GLuint program = LoadShaders( "../shaders/SimpleVertexShader.vertexshader", "../shaders/SimpleFragmentShader.fragmentshader" );
    setShaderProgram(program);

    setPositionsBuffer();

}

void Renderer::setPositionsBuffer(){
    GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &vao_ID);
    glDeleteBuffers(1, &vbo_ID);
}


void Renderer::init(){
    glGenVertexArrays(1, &tileVAO);
    glBindVertexArray(tileVAO);

    glGenBuffers(1, &tileVBO);
    glBindBuffer(GL_ARRAY_BUFFER, tileVBO);

    // Specify the layout of the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    
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
    for (int i = 0; i < worldMap.size(); ++i) {
       for (int j = 0; j < worldMap[0].size(); ++j) {
            std::cout << worldMap[i][j] << " ";
        }
        std::cout << std::endl;
    }



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

void Renderer::renderTile(int startX, int startY, int tileValue) {
    
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Render tile
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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