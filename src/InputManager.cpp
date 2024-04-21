#include "InputManager.hpp"

InputManager::InputManager(GLFWwindow* window){
    init(window);
}

void InputManager::init(GLFWwindow* window){
    i_window = window;
}

bool isKeyPressed(int key){return false;}

std::pair<int, int> getMousePosition(){
    return {0, 0};
}