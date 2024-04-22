#include "Game.hpp"

Game::Game()
    : window(800, 800, "Game"), inputManager(window.getWindow()), textureManager(),
    stateController(), renderer(800.0f, 800.0f, 5.0f, 5.0f), physicsEngine(), camera(800, 800, 0, 0), generator()
{
    tileWidth = 5;
    tileHeight = 5;
    screenWidth = 800;
    screenHeight = 800;
    
    renderer.init();
    worldMap = generator.getMap();
    //generator.printMap();

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
    renderer.renderTilemap(0, 0, worldMap);
}
