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

class Graphics {
public:
Graphics();
~Graphics();

void SimulationSetup();
void SimulationLoop();

void mouse_callback();
void zoom_callback();

private:
void RenderingInit();
void RenderingEnd();

/* Additional OpenGL funcitons */
void AcceptInput(GLFWwindow* window);
/* Additional OpenGL funcitons */

// Variables for OpenGL
GLFWwindow* window;
int windowWidth = 800;
int windowHeight = 600;


//Control for the Rotation
double xPos = windowWidth / 2;
double yPos = windowHeight / 2;
double lastXPos, lastYPos;

//Control for the Zoom
float xOffset = 45.0f;
float yOffset = 45.0f;

//There should only be one camera object
std::shared_ptr<Camera> cameraRef = std::make_shared<Camera>();

//Should be able to have any number of Objects
//std::shared_ptr<Gizmos> gizmosRef = std::make_shared<Gizmos>();
std::vector<std::shared_ptr<Gizmos>> gizmosVec;

};

#endif
