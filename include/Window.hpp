#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:

    Window(int width, int height, const char* title);
    ~Window();

    void update();
    void clear();
    bool isOpen() const;
    void pollEvents();
    void swapBuffers();
    GLFWwindow* getWindow();
    void processInput();
    int getWidth() const;
    int getHeight() const;

    // Add more methods as needed for window management

private:
    int width;
    int height;
    const char* title;
    GLFWwindow* window;
    
};

#endif // WINDOW_H
