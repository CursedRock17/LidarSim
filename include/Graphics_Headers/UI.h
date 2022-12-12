#ifndef UI_H
#define UI_H

#include "imgui.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../include/Graphics_Headers/Imgui_OpenGL3_Impl.h"

class UI 
{
public:
UI(GLFWwindow* window, int windowHeight, int windowWidth);
~UI();

void SetupMenu();
void MenuLoop();

private:

// GLFW Window Settings
GLFWwindow* _window;
int _windowHeight;
int _windowWidth;

float lastTime{0.0f};

// Our Main Context for the Menu
ImGuiIO *io;

//Extra Flags
bool darkMode{true};

void DestroyMenu();
};

#endif
