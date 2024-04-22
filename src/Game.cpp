#include "Game.hpp"

Game::Game()
    : window(1200, 600, "Game"), inputManager(window.getWindow()), textureManager(),
    stateController(), renderer(), physicsEngine(), camera(1200, 600)
{
    renderer.init();
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
    renderer.render();
}
