// Fragment Shader
#version 330 core

in vec2 fragTexCoord;

out vec4 fragColor;

uniform sampler2D tileset;

void main() {
    fragColor = texture(tileset, fragTexCoord);
}