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
// Rendering Libraries //

class Gizmos
{	
public:
Gizmos();
~Gizmos();

void BasicMove(unsigned int shaderID);
void CreateShaders(const char* vertexPath, const char* fragmentPath);
void RenderTextures();
void GizmosLoop();

private:

unsigned int VBO, VAO, EBO;
unsigned int shaderProgram;

int verticesAmount = 3;

//Reading from other files
std::ifstream vertexFile;
std::ifstream fragmentFile;
std::string vertexBuffer;
std::string fragmentBuffer;

unsigned int texture;

void GizmosCleanUp();
};

#endif
