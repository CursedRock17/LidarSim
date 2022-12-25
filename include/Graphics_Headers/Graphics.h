#ifndef GRAPHICS_H
#define GRAPHICS_H

// Rendering Libraries //
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// Rendering Libraries //

//Outer Libraries //
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <filesystem>
#include <vector>


// Additional Classes Needed //
#include "../Gizmos_Headers/Gizmos.h"
#include "../Camera_Headers/Camera.h"

class Graphics {
public:
Graphics(GLFWwindow* window, int windowWidth, int windowHeight, std::vector<std::shared_ptr<Gizmos>> gizmosVec);
~Graphics();

void SimulationSetup();
void SimulationLoop();

void mouse_callback();
void zoom_callback();

void RotateCam(float xPosition, float yPosition, bool newClick);
void ZoomCam(bool zoomingIn);
// Simple Object Creation Functions

void CreateCube();
void CreatePyramid();

// Simple Object Creation Functions

void RefreshGizmos();

//Need a public list of Gizmos Because we only change them here and the Application needs access to all of them
std::vector<std::shared_ptr<Gizmos>> GetGizmosVec();
void SetGizmosVec(std::vector<std::shared_ptr<Gizmos>> gizmosVec);


private:
void RenderingInit();
void RenderingEnd();

/* Additional OpenGL funcitons */
void AcceptInput();
/* Additional OpenGL funcitons */

// Variables for OpenGL
GLFWwindow* _window;
int _windowWidth{800};
int _windowHeight{600};

//Control for the Rotation
double xPos = _windowWidth / 2;
double yPos = _windowHeight / 2;
double lastXPos, lastYPos;

//Control for the Zoom
float xOffset{45.0f};
float yOffset{45.0f};

//There should only be one camera object
std::shared_ptr<Camera> cameraRef = std::make_shared<Camera>();

//List of all the Gizmos we are able to change
std::vector<std::shared_ptr<Gizmos>> _gizmosVec;
};


#endif
