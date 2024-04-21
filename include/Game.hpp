#pragma once

#include "Window.hpp"
#include "InputManager.hpp"
#include "TextureManager.hpp"
#include "PhysicsEngine.hpp"
#include "GameStateController.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"

class Game {
public:
    Game();
    ~Game();
    void run();
    void update(int deltaTime);
    void render();

private:
    Window window;
    InputManager inputManager;
    TextureManager textureManager;
    PhysicsEngine physicsEngine;
    GameStateController stateController;
    Camera camera;
    Renderer renderer;

    static const GLfloat vertexBufferData[];
    GLsizei vertexCount;
};