#ifndef GRAPHICS_H
#define GRAPHICS_H

// Rendering Libraries //
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
// Rendering Libraries //

// Additional Classes Needed //
#include "../Gizmos_Headers/Gizmos.h"
#include "../Space_Headers/Space.h"

class Graphics {
public:
Graphics();
~Graphics();

void SimulationSetup();
void SimulationLoop();

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

std::shared_ptr<Space> spaceRef = std::make_shared<Space>();
std::shared_ptr<Gizmos> gizmosRef = std::make_shared<Gizmos>();

};

#endif
