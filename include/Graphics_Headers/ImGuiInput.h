#include "imgui.h"
#include <GLFW/glfw3.h>

//Callback Functions
void ImGui_Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset);
void ImGui_Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void ImGui_Mouse_Button_Callback(GLFWwindow* window, int button, int action, int mods);
void ImGui_Cursor_Pos_Callback(GLFWwindow* window, double xpos, double ypos);
void ImGui_Char_Callback(GLFWwindow* window, unsigned int codepoint);

//Creation Functions
void ImGui_Input_Setup(GLFWwindow* window);
void ImGui_Input_Loop(GLFWwindow* window);
