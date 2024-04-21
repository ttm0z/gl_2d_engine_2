#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>


struct Tileset {
    int tileWidth;
    int tileHeight;
    int columns;
    GLuint texture;
};