#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <iostream>
#include <vector>

class WindowManager {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int screenWidth;
    int screenHeight;
    int gridSize;
    int cellSize;
    std::vector<std::vector<bool>> gridMap;

public:
    WindowManager(int width, int height, int gridSize, std::vector<std::vector<bool>> map);
    ~WindowManager();

    bool init();
    void render(const Camera& camera);
    void close();
    void drawGrid();
    int getScreenWidth() const;
    int getScreenHeight() const;
    SDL_Renderer* getRenderer() const;
};

#endif // WINDOWMANAGER_H
