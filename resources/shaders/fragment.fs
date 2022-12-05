#version 330 core

out vec4 FragTexture;
out vec4 FragColor;

in vec2 TexCoord;

in vec3 Normal;
in vec3 FragPos;

// texture samplers
uniform sampler2D texture0;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightShader;
uniform vec3 viewPos;

struct MaterialMakeup
{
	sampler2D diffuseMap;
	sampler2D specularMap;
};

uniform vec3 ambientStrength;
uniform vec3 specularStrength;
uniform vec3 diffuseStrength;
uniform float shiny;

void main()
{
	vec3 superNormal = normalize(Normal);
	vec3 lightDiffuse = normalize(lightPos - FragPos);
	float diffuseDiff = max(dot(superNormal, lightDiffuse), 0.0);
	vec3 totalDiffuse =  diffuseStrength * diffuseDiff * texture(MaterialMakeup.diffuseMap, TexCoords).rgb;

	vec3 resultantAmbient = ambientStrength * texture(MaterialMakeup.diffuseMap, TexCoords).rgb;
	
	//** For the Specular lighing we can change everything the View Dimension to save resources **//
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflection = reflect(-lightDiffuse, superNormal);
	float specularLighting = pow(max(dot(viewDir, reflection), 0.0), shiny);
	vec3 resultantSpecular = specularStregnth * (specularLighting *  MaterialMakeup.specularMap);

	//Calculate the color with all the different types of lighting and reflection
	FragColor = vec4((resultantAmbient + totalDiffuse + resultantSpecular), 1.0);
	
	FragTexture = texture(texture0, TexCoord);
	
}

