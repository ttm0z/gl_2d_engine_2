#include "Renderer.hpp"
#include "shader.hpp"
#include <iostream>


Renderer::Renderer() : vao_ID(0), vbo_ID(0) {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GLuint program = LoadShaders( "../shaders/SimpleVertexShader.vertexshader", "../shaders/SimpleFragmentShader.fragmentshader" );
    setShaderProgram(program);

}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &vao_ID);
    glDeleteBuffers(1, &vbo_ID);
}


void Renderer::init(){
    glGenVertexArrays(1, &vao_ID);
    glBindVertexArray(vao_ID);

    glGenBuffers(1, &vbo_ID);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ID);

    // Specify the layout of the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind the VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::setShaderProgram(GLuint programID){
    glUseProgram(programID);
}

void Renderer::render(const GLfloat* vertexData, GLsizei vertexCount) {
    // Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rendering logic goes here
    // A Simple Example: draw a triangle

    glBindVertexArray(vao_ID);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_ID);

    // Update vertex buffer data
    glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

    // Draw the vertices
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}