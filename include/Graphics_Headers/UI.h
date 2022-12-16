#ifndef UI_H
#define UI_H

#include <iostream>
#include <vector>
#include <memory>

#include "imgui.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../include/Graphics_Headers/Imgui_OpenGL3_Impl.h"
#include "../../include/Graphics_Headers/Graphics.h"
#include "../../include/Gizmos_Headers/Gizmos.h"
#include "./ImGuiInput.h"

class UI 
{
public:
UI(GLFWwindow* window, int windowHeight, int windowWidth, std::vector<std::shared_ptr<Gizmos>> gizmosVec);
~UI();

void SetupMenu(std::shared_ptr<Graphics> GraphicsRef);
void MenuLoop(std::shared_ptr<Graphics> GraphicsRef);

void MenuEventHandler();

private:

void mouse_callback();
void zoom_callback();

// GLFW Window Settings
GLFWwindow* _window;
int _windowHeight;
int _windowWidth;

float lastTime{0.0f};

//Control for the Rotation
double xPos = _windowWidth / 2;
double yPos = _windowHeight / 2;
double lastXPos, lastYPos;

//Control for the Zoom
float xOffset{45.0f};
float yOffset{45.0f};

// Our Main Context for the Menu
ImGuiIO *io;
std::vector<std::shared_ptr<Gizmos>> _gizmosVec;

//Extra Flags
bool darkMode{true};

void DestroyMenu();
};

#endif
