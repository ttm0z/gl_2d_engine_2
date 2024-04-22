#pragma once

#include "Window.hpp"
#include "InputManager.hpp"
#include "TextureManager.hpp"
#include "PhysicsEngine.hpp"
#include "GameStateController.hpp"
#include "Camera.hpp"
#include "WorldGenerator.hpp"
#include "Renderer.hpp"

class Game {
public:
    Game();
    ~Game();
    void run();
    void update(int deltaTime);
    void render();

    int tileWidth;
    int tileHeight;
    int screenWidth;
    int screenHeight;

private:
    Window window;
    InputManager inputManager;
    TextureManager textureManager;
    PhysicsEngine physicsEngine;
    GameStateController stateController;
    Camera camera;
    Renderer renderer;
    WorldGenerator generator;
    std::vector<std::vector<int>> worldMap;

    static const GLfloat vertexBufferData[];
    GLsizei vertexCount;
};