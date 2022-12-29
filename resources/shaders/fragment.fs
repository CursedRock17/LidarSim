#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

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

uniform MaterialMakeup material;

void main()
{
	//Ambient
	vec3 resultantAmbient = ambientStrength * vec3(texture(material.diffuseMap, TexCoord));
	
	//Diffuse
	vec3 superNormal = normalize(Normal);
	vec3 lightDiffuse = normalize(lightPos - FragPos);
	float diffuseDiff = max(dot(superNormal, lightDiffuse), 0.0);
	vec3 totalDiffuse = diffuseStrength * diffuseDiff * vec3(texture(material.diffuseMap, TexCoord));

	//** For the Specular lighing we can change everything the View Dimension to save resources **//
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflection = reflect(-lightDiffuse, superNormal);
	float specularLighting = pow(max(dot(viewDir, reflection), 0.0), shiny);
	vec3 resultantSpecular = specularStrength * specularLighting * vec3(texture(material.specularMap, TexCoord));

	//Calculate Alpha Values if any;
	vec4 textureAlpha = texture(material.diffuseMap, TexCoord);
	if(textureAlpha.a < 0.1)
		discard;

	//Calculate the color with all the different types of lighting and reflection
	FragColor = vec4((objectColor + resultantAmbient + totalDiffuse + resultantSpecular), textureAlpha.a);
}

