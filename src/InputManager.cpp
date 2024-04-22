#include "InputManager.hpp"
#include <iostream>

InputManager::InputManager(GLFWwindow* window){
    std::cout << "Input Manager Initialized" << std::endl;
    init(window);
}

void InputManager::init(GLFWwindow* window){
    i_window = window;
}

bool isKeyPressed(int key){return false;}

std::pair<int, int> getMousePosition(){
    return {0, 0};
} 