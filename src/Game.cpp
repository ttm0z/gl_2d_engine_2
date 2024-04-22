#include "Game.hpp"

Game::Game()
    : window(1200, 600, "Game"), inputManager(window.getWindow()), textureManager(),
    stateController(), renderer(), physicsEngine(), camera(800, 800, 200, 200)
{
    tileWidth = 32;
    tileHeight = 32;
    screenWidth = 800;
    screenHeight = 800;
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
