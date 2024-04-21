#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <utility>      // std::pair

class InputManager{
    InputManager(GLFWwindow* window);
    bool isKeyPressed(int key);
    std::pair<int, int> getMousePosition();
};