#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include "LoadShaderGeo.hpp"

GLuint LoadShadersWithGeo(const char * vertex_file_path, const char * geometry_file_path, const char * fragment_file_path) {

    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint GeometryShaderID = 0; // Initialize to 0
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read and compile vertex shader
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    } else {
        printf("Impossible to open %s. Are you in the right directory ?\n", vertex_file_path);
        return 0;
    }

    // Compile vertex shader
    GLint Result = GL_FALSE;
    int InfoLogLength;
    printf("Compiling shader : %s\n", vertex_file_path);
    const char* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    // Check vertex shader compilation
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    // Read and compile geometry shader if provided
    if (geometry_file_path != nullptr) {
        std::string GeometryShaderCode;
        std::ifstream GeometryShaderStream(geometry_file_path, std::ios::in);
        if (GeometryShaderStream.is_open()) {
            std::stringstream sstr;
            sstr << GeometryShaderStream.rdbuf();
            GeometryShaderCode = sstr.str();
            GeometryShaderStream.close();
        } else {
            printf("Impossible to open %s. Are you in the right directory ?\n", geometry_file_path);
            return 0;
        }

        // Compile geometry shader
        printf("Compiling shader : %s\n", geometry_file_path);
        GeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
        const char* GeometrySourcePointer = GeometryShaderCode.c_str();
        glShaderSource(GeometryShaderID, 1, &GeometrySourcePointer, NULL);
        glCompileShader(GeometryShaderID);

        // Check geometry shader compilation
        glGetShaderiv(GeometryShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(GeometryShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> GeometryShaderErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(GeometryShaderID, InfoLogLength, NULL, &GeometryShaderErrorMessage[0]);
            printf("%s\n", &GeometryShaderErrorMessage[0]);
        }
    }

    // Read and compile fragment shader
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    } else {
        printf("Impossible to open %s. Are you in the right directory ?\n", fragment_file_path);
        return 0;
    }

    // Compile fragment shader
    printf("Compiling shader : %s\n", fragment_file_path);
    const char* FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    // Check fragment shader compilation
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Create shader program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    if (geometry_file_path != nullptr) {
        glAttachShader(ProgramID, GeometryShaderID);
    }
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check shader program linking
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    // Clean up shaders
    glDetachShader(ProgramID, VertexShaderID);
    if (geometry_file_path != nullptr) {
        glDetachShader(ProgramID, GeometryShaderID);
        glDeleteShader(GeometryShaderID);
    }
    glDetachShader(ProgramID, FragmentShaderID);
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}
