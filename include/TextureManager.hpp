#pragma once
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

class TextureManager {
public:
    TextureManager();
    GLuint loadTexture(const std::string& path);
    GLuint getTexture(const std::string& path);
    
    
    std::unordered_map<std::string, GLuint> textures;

};