#pragma once

#include "Window.hpp"
#include "InputManager.hpp"
#include "TextureManager.hpp"
#include "PhysicsEngine.hpp"
#include "GameStateController.hpp"
#include "Camera.hpp"

class Game {
public:
    Game();
    ~Game();
    void init();
    void run();
    void update(int deltaTime);
    void render();

private:
    Window* window;
    InputManager inputManager;
    TextureManager textureManager;
    PhysicsEngine physicsEngine
    GameStateController stateController;
    Camera camera;
};
