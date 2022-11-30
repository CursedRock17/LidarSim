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
void RenderTextures(const char* imgLocation);

void GizmosLoop();
void RenderContainer();

unsigned int shaderProgram;

//Setting Features for Each Object
glm::vec3 SetRotation(float xRotation, float yRotation, float zRotation);
glm::vec3 SetTranslation(float xTranslation, float yTranslation, float zTranslation);
glm::vec3 SetScale(float xScale, float yScale, float zScale);
glm::vec3 SetColor(float red, float green, float blue);

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
unsigned int texture0;

//Reading from other files
std::ifstream vertexFile;
std::ifstream fragmentFile;
std::string vertexBuffer;
std::string fragmentBuffer;

void GizmosCleanUp();
};

#endif
