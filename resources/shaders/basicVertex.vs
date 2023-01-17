#version 330 core

uniform mat4 model;
uniform mat4 viewer;
uniform mat4 perspective;

void main(){
    gl_Position = perspective * viewer * model * vec4(0.0f, 0.0f, 0.0f, 1.0f);
}
