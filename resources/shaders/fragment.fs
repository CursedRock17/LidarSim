#version 330 core


out vec4 FragTexture;
out vec4 FragColor;

in vec2 TexCoord;

uniform vec3 normal;
uniform vec3 fragPos;

// texture samplers
uniform sampler2D texture0;
uniform sampler2D texture1;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightShader;

void main()
{
	vec3 superNormal = normalize(normal);
	vec3 lightDiffuse = normalize(lightPos - fragPos);
	float diffuseDiff = max(dot(superNormal, lightDiffuse), 0.0);
	vec3 totalDiffuse = diffuseDiff * lightShader; 


	float ambientStrength = 0.5f;
	vec3 resultantAmbient = ambientStrength * lightShader;
	FragColor = vec4((resultantAmbient + totalDiffuse) * objectColor, 1.0);

	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragTexture = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.2);
	



}

