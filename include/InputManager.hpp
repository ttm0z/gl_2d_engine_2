#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <utility>      // std::pair

class InputManager{
public:
    InputManager(GLFWwindow* window);
    void init(GLFWwindow* window);
    bool isKeyPressed(int key);
    std::pair<int, int> getMousePosition();
private:
    GLFWwindow* i_window;
};