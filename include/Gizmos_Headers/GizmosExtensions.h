#ifndef GIZMOSEXTENSIONS_H
#define GIZMOSEXTENSIONS_H

//Simple Libraries
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <vector>
#include <iostream>

// Rendering Libraries //
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// Rendering Libraries //

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Start of Shader Class

class Shader {
public:
Shader();
~Shader();

unsigned int shaderProgram;
void CreateShaders(const char* vertexPath, const char* fragmentPath);
	
private:
std::ifstream vertexFile;
std::ifstream fragmentFile;
std::string vertexBuffer;
std::string fragmentBuffer;
};

//End of Shader Class

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

class InstancedObject {
public:	
InstancedObject();
~InstancedObject();

void PrepareObjects(std::vector<float> vertices, int objectPoints, int objectAmount);
void RenderingLoop();

private:
int totalObjectPoints, objectCount;
unsigned int VBO;

};

class DrawnNonGizmo {
public:
DrawnNonGizmo();
~DrawnNonGizmo();

void CreateBuffers();
void RenderBuffers();

void CreateGrid();

private:
void DestroyBuffers();
	Shader shad;
unsigned int VAO, VBO;

int Spacing, SizeTaken;
std::vector<glm::vec3> floorVertices;

};
#endif
