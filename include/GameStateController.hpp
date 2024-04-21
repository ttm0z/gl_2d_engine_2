#pragma once

class GameStateController {
public:
// add more states as needed

    GameStateController();
    enum class GameState {Menu, Play, Pause, Options};
    void setState(GameState state);
    GameState getState();
};