#ifndef GRAPHICS_H
#define GRAPHICS_H

// Rendering Libraries //
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
// Rendering Libraries //
class Graphics {
public:
Graphics();
~Graphics();

void RenderingLoop();

private:
void RenderingInit();
void RenderingEnd();

/* Additional OpenGL funcitons */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void AcceptInput(GLFWwindow* window);
/* Additional OpenGL funcitons */

// Variables for OpenGL
GLFWwindow* window;
int windowWidth = 800;
int windowHeight = 600;

};

#endif