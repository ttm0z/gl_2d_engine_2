#include "GameStateController.hpp"
#include <iostream>

GameStateController::GameStateController() {
    
    std::cout << "statemanager initialized" <<std::endl;
    // Initialize the state to the default state, e.g., Menu
    currentState = GameState::Menu;
}

void GameStateController::setState(GameState state) {
    currentState = state;
}

GameStateController::GameState GameStateController::getState() {
    return currentState;
}
