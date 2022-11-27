#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 texCoords;

out vec3 vertexColor;

uniform mat4 spaceTransform;
uniform mat4 viewer;
uniform mat4 perspective;

void main(){
    gl_Position = perspective * viewer * spaceTransform * vec4(aPos, 1.0f);
    vertexColor = aColor;
}
