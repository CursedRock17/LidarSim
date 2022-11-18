#ifndef GRAPHICS_H

#define GRAPHICS_H

// Rendering Libraries //
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
// Rendering Libraries //


class Graphics {
public:
Graphics();
~Graphics();

void RenderingLoop();
void CreateShaders();
void RenderTextures();

private:
void RenderingInit(const char* vertexPath, const char* fragmentPath);
void RenderingEnd();

/* Additional OpenGL funcitons */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void AcceptInput(GLFWwindow* window);
/* Additional OpenGL funcitons */

// Variables for OpenGL
GLFWwindow* window;
int windowWidth = 800;
int windowHeight = 600;

unsigned int VBO, VAO, EBO;
unsigned int shaderProgram;

int verticesAmount = 3;

//Reading from other files
std::ifstream vertexFile;
std::ifstream fragmentFile;
std::string vertexBuffer;
std::string fragmentBuffer;


unsigned int texture;

};

#endif
