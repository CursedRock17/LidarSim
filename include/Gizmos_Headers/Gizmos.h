#ifndef GIZMOS_H
#define GIZMOS_H
       
//Math libraries from opengl, needed for things like rotational matrices and dot products
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Rendering Libraries //
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
// Rendering Libraries //

class Gizmos
{	
public:
Gizmos();
~Gizmos();

void BasicMove();

void CreateShaders(const char* vertexPath, const char* fragmentPath);
void CreateTextures(int totPoints, std::vector<unsigned int> indies, std::vector<float> verts);
void RenderTextures(const char* imgLocation, const char* specularMapLocation);

void GizmosInit();

void GizmosLoop(glm::mat4 viewMatrix, float& screenAspect, float &FOV, bool hasTexture);
void RenderContainer();

unsigned int shaderProgram;

//Setting Features for Each Object
glm::vec3 SetRotation(float xRotation, float yRotation, float zRotation);
glm::vec3 SetTranslation(float xTranslation, float yTranslation, float zTranslation);
glm::vec3 SetScale(float xScale, float yScale, float zScale);
glm::vec3 SetColor(float red, float green, float blue);
glm::vec3 SetLightPosition(float xCoord, float yCoord, float zCoord);
glm::vec3 SetViewPos(float xCoord, float yCoord, float zCoord);


//Override setFunction for equivelency across all axis
glm::vec3 SetRotation(float totalRotation);
glm::vec3 SetTranslation(float totalTranslation);
glm::vec3 SetScale(float totalScale);
glm::vec3 SetColor(float totalColor);
glm::vec3 SetLightPosition(float totalPosition);

glm::vec3 SetViewPos(float totalPosition);
glm::vec3 SetViewPos(glm::vec3 vectorPosition);

int ID;
std::string objectName;

private:
unsigned int VBO, VAO, EBO;

//Describing the Object to Create
int totalVerticeArgs;
int totalVerticeShaderArgs;

//Where the Object is in Space: These methods are handled with setter functions
glm::vec3 Rotation = glm::vec3(1.0f, 0.3f, 0.5f);
glm::vec3 Translation = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Scale = glm::vec3(1.0f);

//Coloring for the object
glm::vec3 lightShader = glm::vec3(1.0f);
glm::vec3 objectColor = glm::vec3(1.0f);
glm::vec3 lightPosition = glm::vec3(1.0f);
glm::vec3 viewPosition = glm::vec3(1.0f);

unsigned int imgMap, imgSpecularMap;
glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

glm::vec3 ambientStrength = glm::vec3(0.2f);
glm::vec3 specularStrength = glm::vec3(1.0f);
glm::vec3 diffuseStrength = glm::vec3(0.5f);
float specularShiny = 64.0f;

void TexturesLoop();

//Reading from other files
std::ifstream vertexFile;
std::ifstream fragmentFile;
std::string vertexBuffer;
std::string fragmentBuffer;

void GizmosCleanUp();
};

#endif
