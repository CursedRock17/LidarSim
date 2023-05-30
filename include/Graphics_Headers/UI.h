#ifndef UI_H
#define UI_H

#include <iostream>
#include <vector>
#include <memory>
#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"

#include "../../include/Graphics_Headers/Imgui_OpenGL3_Impl.h"
#include "../../include/Graphics_Headers/FolderUI.h"
#include "../../include/Graphics_Headers/Graphics.h"
#include "../../include/Gizmos_Headers/Gizmos.h"

#include "../../include/Application_Headers/Universal_Consts.h"
#include "./ImGuiInput.h"

class UI
{
public:
UI(GLFWwindow* window, int windowHeight, int windowWidth, std::vector<std::shared_ptr<Gizmos>> gizmosVec);
~UI();

virtual void SetupMenu();
virtual void MenuLoop(std::shared_ptr<Graphics> _GraphicsRef, std::string* application_mode);

void SetGizmosVec(std::vector<std::shared_ptr<Gizmos>> gizmosVec);
void SetRenderedTexture(unsigned int _RTO);

float sceneWidth;
float sceneHeight;

// ** If ever want polymorphic class make these virtual
void mouse_callback(std::shared_ptr<Graphics> _GraphicsRef);
void accept_input(std::shared_ptr<Graphics> _GraphicsRef);

void ImGuiContextLoop();

// GLFW Window Settings
GLFWwindow* _window;
int _windowHeight;
int _windowWidth;

float time{0.0f};
float lastTime{0.0f};

//Control for the Rotation
double xPos = _windowWidth / 2;
double yPos = _windowHeight / 2;
double lastXPos, lastYPos;

//Control for the Zoom
float xOffset{45.0f};
float yOffset{45.0f};

//Display Details
int tempW, tempH;
int displayW, displayH;

//Extra Flags
bool darkMode{true};
bool sceneFocused{false};
bool show{true};


// Our Main Context for the Menu
ImGuiIO *io;
ImGuiStyle  *style;

std::vector<std::shared_ptr<Gizmos>> _gizmosVec;
unsigned int RTO;
std::shared_ptr<Gizmos> activeGizmo = nullptr;

//Specialized Functions for ImGui
static bool ImGui_InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = 0);
static int StringResizeCallback(ImGuiInputTextCallbackData* data);

void SetupStyles();
FolderUI Folder;

void DestroyMenu();
};

class MainUI : public UI {
public:
MainUI(GLFWwindow* window, int windowHeight, int windowWidth, std::vector<std::shared_ptr<Gizmos>> gizmosVec);
~MainUI();

void SetupMenu();
void MenuLoop(std::shared_ptr<Graphics> _GraphicsRef, std::string* application_mode);

float sceneWidth;
float sceneHeight;

private:

void mouse_callback(std::shared_ptr<Graphics> _GraphicsRef);
void accept_input(std::shared_ptr<Graphics> _GraphicsRef);


};

#endif

