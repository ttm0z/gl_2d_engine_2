#version 330 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform vec2 tileSize;
uniform ivec2 mapSize;

in vec2 texCoord[];

out vec2 fragTexCoord;

void main() {
    for (int x = 0; x < mapSize.x; ++x) {
        for (int y = 0; y < mapSize.y; ++y) {
            vec2 tilePosition = vec2(x * tileSize.x, y * tileSize.y);
            gl_Position = vec4(tilePosition, 0.0, 1.0);
            fragTexCoord = texCoord[0];
            EmitVertex();
            
            gl_Position = vec4(tilePosition.x + tileSize.x, tilePosition.y, 0.0, 1.0);
            fragTexCoord = texCoord[1];
            EmitVertex();
            
            gl_Position = vec4(tilePosition.x, tilePosition.y + tileSize.y, 0.0, 1.0);
            fragTexCoord = texCoord[2];
            EmitVertex();
            
            gl_Position = vec4(tilePosition + tileSize, 0.0, 1.0);
            fragTexCoord = texCoord[3];
            EmitVertex();
            
            EndPrimitive();
        }
    }
}