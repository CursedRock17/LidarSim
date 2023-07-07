#ifndef GIZMOS_H
#define GIZMOS_H

//Math libraries from opengl, needed for things like rotational matrices and dot products
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Rendering Libraries //
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
// Rendering Libraries //

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>

#include "./GizmosExtensions.h"
#include "../Graphics_Headers/UIElements.h"

class Gizmos
{
public:
Gizmos();
~Gizmos();

void CreateShaders(const char* vertexPath, const char* fragmentPath);
void CreateTextures(int totPoint, std::vector<float> verts, std::vector<int> _indices);

void RenderTextures();

virtual void GizmosInit();

virtual void GizmosLoop(glm::mat4 viewMatrix, float& screenAspect, float &FOV);
virtual void GizmosUILoop();

void RenderContainer();
//Theis will represent instancing
void RenderContainer(int numObjects);

Shader shad;
unsigned int shaderProgram;

//Setting Features for Each Object
glm::vec3 SetRotation(float xRotation, float yRotation, float zRotation);
glm::vec3 SetTranslation(float xTranslation, float yTranslation, float zTranslation);
glm::vec3 SetScale(float xScale, float yScale, float zScale);
glm::vec3 SetLightPosition(float xCoord, float yCoord, float zCoord);
glm::vec3 SetViewPos(float xCoord, float yCoord, float zCoord);
void SetMaterialStrengths(float asd[]);
void SetMaterialShine(float materialShine);

//Override setFunction for equivelency across all axis
glm::vec3 SetRotation(float totalRotation);
glm::vec3 SetTranslation(float totalTranslation);
glm::vec3 SetLightPosition(float totalPosition);
glm::vec3 SetScale(float totalScale);
glm::vec3 SetViewPos(float totalPosition);
glm::vec3 SetViewPos(glm::vec3 vectorPosition);

//Updating Features by applying to the model for Each Object
glm::vec3 UpdateRotation(float xRotation, float yRotation, float zRotation);
glm::vec3 UpdateTranslation(float xTranslation, float yTranslation, float zTranslation);
glm::vec3 UpdateScale(float xScale, float yScale, float zScale);

//Override UpdateObject for equivelency across all axis
glm::vec3 UpdateRotation(float totalRotation);
glm::vec3 UpdateTranslation(float totalTranslation);
glm::vec3 UpdateScale(float totalScale);

//All the Getter functions
glm::vec3 GetRotation();
glm::vec3 GetTranslation();
glm::vec3 GetScale();
glm::vec3 GetMaterialStrengths();
float GetMaterialShine();

void ResetGizmoSpace(); // Set all the world space values to the default
void UpdateGizmoSpace(); // Set the values of the gizmo for the world space

int ID;
std::string objectName;

bool hasTexture{false};

// Simple Example Creations
bool CreateCustomGizmo(const std::string& filePath);

void TexturesLoop();
void GizmosCleanUp();

// Simple Example Creations
unsigned int VBO, VAO, EBO;
unsigned int modelLoc;

//Describing the Object to Create
int totalVerticeArgs;
int totalVerticeShaderArgs;

unsigned int imgMap, imgSpecularMap;
glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

// Lighting for the Gizmo
glm::vec3 lightShader = glm::vec3(1.0f);
glm::vec3 lightPosition = glm::vec3(1.0f);
glm::vec3 viewPosition = glm::vec3(1.0f);

glm::vec3 ambientStrength = glm::vec3(0.2f);
glm::vec3 specularStrength = glm::vec3(0.5f);
glm::vec3 diffuseStrength = glm::vec3(0.5f);
float specularShiny = 64.0f;

//Where the Object is in Space: These methods are handled with setter functions
glm::vec3 Rotation = glm::vec3(0.0f);
glm::vec3 Translation = glm::vec3(0.0f);
glm::vec3 Scale = glm::vec3(1.0f);

//Reading from other files
std::ifstream vertexFile;
std::ifstream fragmentFile;
std::string vertexBuffer;
std::string fragmentBuffer;

// Element builder object : init in constructor
std::unique_ptr<ElementsBuilder> ElementUI;

};

// End of Gizmo Class
//

class BasicGizmo : public Gizmos {
public:
BasicGizmo();
~BasicGizmo();

// Overriden Functions for color and lighting
virtual void GizmosInit();
virtual void GizmosLoop(glm::mat4 viewMatrix, float& screenAspect, float &FOV);
virtual void GizmosUILoop();
void RenderTextures();

// Setter functions for the builder class
glm::vec3 SetColor(float rgb[]);

// Overridden set functions for constant values in the vector
glm::vec3 SetColor(float totalColor);

// Getter Functions for Builder Class
glm::vec3 GetColor();

std::filesystem::path specularLocation{""};
std::filesystem::path diffuseLocation{""};

// Simple Creation Methods
void CreateCube();
void CreatePyramid();
void CreateLight();
void CreateFloor();
private:

//Coloring for the object
glm::vec3 objectColor = glm::vec3(1.0f);


};
// End of CustomGizmo Class



#endif
