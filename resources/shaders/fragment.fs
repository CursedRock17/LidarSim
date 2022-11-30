#version 330 core


out vec4 FragTexture;
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture0;
uniform sampler2D texture1;

uniform vec3 objectColor;
uniform vec3 lightShader;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragTexture = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.2);
	FragColor = vec4(lightShader * objectColor, 1.0);
}

