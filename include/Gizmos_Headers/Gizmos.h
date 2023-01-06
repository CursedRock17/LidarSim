#ifndef GIZMOS_H
#define GIZMOS_H
       
//Math libraries from opengl, needed for things like rotational matrices and dot products
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Rendering Libraries //
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// Rendering Libraries //

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>


// Start of Framebuffer Class

class Framebuffer {
public:

Framebuffer();
~Framebuffer();

void FramebufferTexture(int imageH, int imageW);
void BindFramebuffer();
void UnbindFramebuffer();

unsigned int GetFramebufferTexture();

private:
//If we need to transform a texture into an image use this stuff
unsigned int RTO, FBO, DBO;

};

// End of Framebuffer Class

class Gizmos
{	
public:
Gizmos();
~Gizmos();

void CreateShaders(const char* vertexPath, const char* fragmentPath);
void CreateTextures(int totPoint, std::vector<float> verts);
void RenderTextures(const char* imgLocation, const char* specularMapLocation);

void GizmosInit();

void GizmosLoop(glm::mat4 viewMatrix, float& screenAspect, float &FOV);

void RenderContainer();

unsigned int shaderProgram;

//Setting Features for Each Object
glm::vec3 SetRotation(float xRotation, float yRotation, float zRotation);
glm::vec3 SetTranslation(float xTranslation, float yTranslation, float zTranslation);
glm::vec3 SetScale(float xScale, float yScale, float zScale);
glm::vec3 SetColor(float red, float green, float blue);
glm::vec3 SetLightPosition(float xCoord, float yCoord, float zCoord);
glm::vec3 SetViewPos(float xCoord, float yCoord, float zCoord);
void SetMaterialStrengths(float ambient, float specular, float diffuse);
void SetMaterialShine(float materialShine);

//Override setFunction for equivelency across all axis
glm::vec3 SetRotation(float totalRotation);
glm::vec3 SetTranslation(float totalTranslation);
glm::vec3 SetScale(float totalScale);
glm::vec3 SetColor(float totalColor);
glm::vec3 SetLightPosition(float totalPosition);
glm::vec3 SetViewPos(float totalPosition);
glm::vec3 SetViewPos(glm::vec3 vectorPosition);

//All the Getter functions
glm::vec3 GetRotation();
glm::vec3 GetTranslation();
glm::vec3 GetScale();
glm::vec3 GetColor();
glm::vec3 GetMaterialStrengths();
float GetMaterialShine();

void ResetGizmoSpace(); // Set all the world space values to the default
void UpdateGizmoSpace(); // Set the values of the gizmo for the world space

int ID;
std::string objectName;
bool hasTexture{false};

// Simple Example Creations

void CreateCube();
void CreatePyramid();
void CreateLight();

// Simple Example Creations
private:
unsigned int VBO, VAO;

//Describing the Object to Create
int totalVerticeArgs;
int totalVerticeShaderArgs;

//Where the Object is in Space: These methods are handled with setter functions
glm::vec3 Rotation = glm::vec3(0.0f);
glm::vec3 Translation = glm::vec3(0.0f);
glm::vec3 Scale = glm::vec3(1.0f);

//Coloring for the object
glm::vec3 lightShader = glm::vec3(1.0f);
glm::vec3 objectColor = glm::vec3(1.0f);
glm::vec3 lightPosition = glm::vec3(1.0f);
glm::vec3 viewPosition = glm::vec3(1.0f);

unsigned int imgMap, imgSpecularMap;
glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

glm::vec3 ambientStrength = glm::vec3(0.2f);
glm::vec3 specularStrength = glm::vec3(0.5f);
glm::vec3 diffuseStrength = glm::vec3(0.5f);
float specularShiny = 64.0f;

//Reading from other files
std::ifstream vertexFile;
std::ifstream fragmentFile;
std::string vertexBuffer;
std::string fragmentBuffer;

void TexturesLoop();
void GizmosCleanUp();
};

// End of Gizmo Class
//




#endif
