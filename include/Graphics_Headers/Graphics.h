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
#include "../Camera_Headers/Camera.h"
#include "../Graphics_Headers/UI.h"

class Graphics {
public:
Graphics();
~Graphics();

void SimulationSetup();
void SimulationLoop();

void mouse_callback();
void zoom_callback();

// Simple Object Creation Functions

void CreateCube();
void CreatePyramid();

// Simple Object Creation Functions

private:
void RenderingInit();
void RenderingEnd();

/* Additional OpenGL funcitons */
void AcceptInput(GLFWwindow* window);
/* Additional OpenGL funcitons */

// Variables for OpenGL
GLFWwindow* window;
static constexpr int windowWidth{800};
static constexpr int windowHeight{600};

//Control for the Rotation
double xPos = windowWidth / 2;
double yPos = windowHeight / 2;
double lastXPos, lastYPos;

//Control for the Zoom
float xOffset{45.0f};
float yOffset{45.0f};

//There should only be one camera object
std::shared_ptr<Camera> cameraRef = std::make_shared<Camera>();
std::shared_ptr<UI> uiRef; 

//Should be able to have any number of Objects
std::vector<std::shared_ptr<Gizmos>> gizmosVec;


};

#endif
