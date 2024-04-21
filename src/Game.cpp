#include "Game.hpp"

const GLfloat Game::vertexBufferData[] = { 
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
};

Game::Game()
    : window(1200, 600, "Game"), inputManager(window.getWindow()), textureManager(),
    stateController(), renderer(), physicsEngine(), camera(1200, 600)
{
    vertexCount = sizeof(vertexBufferData) / (3 * sizeof(GLfloat));
}



Game::~Game()
{
}

void Game::run()
{
    double lastFrameTime = glfwGetTime();

    while(window.isOpen()){
        
        double currentFrameTime = glfwGetTime();
        double deltaTime = currentFrameTime - lastFrameTime;
        
        update(deltaTime);

        render();
    }
}

void Game::update(int deltaTime)
{
    window.update();
}

void Game::render()
{
    renderer.render(vertexBufferData, vertexCount);
}
