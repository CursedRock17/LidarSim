#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

out vec3 Color;
out vec2 TexCoord;

out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 viewer;
uniform mat4 perspective;

void main(){
    normal = aNormal;
    fragPos = vec3(model * vec4(aPos, 1.0));

    gl_Position = perspective * viewer * model * vec4(aPos, 1.0f);
    Color = aColor;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}

