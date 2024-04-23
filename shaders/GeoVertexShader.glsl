// Vertex Shader
#version 330 core

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec2 inTexCoord;

out vec2 texCoord;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main() {
    texCoord = inTexCoord;
    gl_Position = projectionMatrix * viewMatrix * vec4(inPosition, 0.0, 1.0);
}