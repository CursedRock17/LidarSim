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

#include "../../include/Application_Headers/Universal_Consts.h"
#include "./ImGuiInput.h"

class UI 
{
public:
UI(GLFWwindow* window, int windowHeight, int windowWidth, std::vector<std::shared_ptr<Gizmos>> gizmosVec);
~UI();

virtual void SetupMenu();
virtual void MenuLoop(std::shared_ptr<Graphics> _GraphicsRef);

void MenuEventHandler();

void SetGizmosVec(std::vector<std::shared_ptr<Gizmos>> gizmosVec);
void SetRenderedTexture(unsigned int _RTO);

float sceneWidth;
float sceneHeight;


virtual void mouse_callback(std::shared_ptr<Graphics> _GraphicsRef);
virtual void zoom_callback(std::shared_ptr<Graphics> _GraphicsRef);
virtual void accept_input(std::shared_ptr<Graphics> _GraphicsRef);

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

// Our Main Context for the Menu
ImGuiIO *io;
std::vector<std::shared_ptr<Gizmos>> _gizmosVec;
unsigned int RTO;

void DestroyMenu();
};

class SceneUI : public UI
{
	public:
	SceneUI(GLFWwindow* window, int windowHeight, int windowWidth, std::vector<std::shared_ptr<Gizmos>> gizmosVec);
	~SceneUI();

	virtual void SetupMenu();
	virtual void MenuLoop(std::shared_ptr<Graphics> _GraphicsRef);

	private:
	virtual void mouse_callback(std::shared_ptr<Graphics> _GraphicsRef);
	virtual void zoom_callback(std::shared_ptr<Graphics> _GraphicsRef);
	virtual void accept_input(std::shared_ptr<Graphics> _GraphicsRef);
};

#endif
