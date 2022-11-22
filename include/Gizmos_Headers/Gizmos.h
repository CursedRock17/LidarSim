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
void CreateShaders(const char* vertexPath, const char* fragmentPath, int totPoints, std::vector<float> verts, std::vector<unsigned int> indies);
void RenderTextures();
void GizmosLoop();

private:

unsigned int VBO, VAO, EBO;
unsigned int shaderProgram;

//Describing the Object to Create
int verticesAmount = 3;
int totalPoints;
std::vector<float> vertices;
std::vector<unsigned int> indicies;

//Reading from other files
std::ifstream vertexFile;
std::ifstream fragmentFile;
std::string vertexBuffer;
std::string fragmentBuffer;

unsigned int texture;
void GizmosCleanUp();
};

#endif
