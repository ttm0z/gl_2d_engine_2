#include "TextureManager.hpp"

TextureManager::TextureManager() {
    // Initialize the map with an empty unordered_map
    textures = std::unordered_map<std::string, GLuint>();
}

GLuint TextureManager::loadTexture(const std::string& path) {
    // Implementation for loading texture
    // Example: You can load the texture from the file system and return its GLuint
    return 0;
}

GLuint TextureManager::getTexture(const std::string& path) {
    // Implementation for getting texture
    // Example: You can retrieve the texture GLuint from the map based on the path
    return 0;
}