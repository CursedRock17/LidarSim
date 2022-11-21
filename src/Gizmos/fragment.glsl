#version 330 core

out vec4 FragColor;
in vec3 vertexColor;
in vec2 textureCoordinate;

uniform sampler2D ourTexture;

void main(){
    FragColor = texture(ourTexture, textureCoordinate);
}
