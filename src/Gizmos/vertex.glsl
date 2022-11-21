#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexture;

out vec3 vertexColor;
out vec2 textureCoordinate;

uniform mat4 spaceTransform;

void main(){
    gl_Position = spaceTransform * vec4(aPos, 1.0f);
    vertexColor = aColor;
    textureCoordinate = vec2(aTexture.x, aTexture.y);
}
