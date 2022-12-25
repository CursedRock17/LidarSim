#include "imgui.h"
#include <GLFW/glfw3.h>

//Callback Functions
void ImGui_Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset);
void ImGui_Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void ImGui_Mouse_Button_Callback(GLFWwindow* window, int button, int action, int mods);
void ImGui_Cursor_Pos_Callback(GLFWwindow* window, double xpos, double ypos);
void ImGui_Char_Callback(GLFWwindow* window, unsigned int codepoint);

//Translation Fucntions
ImGuiKey GLFW_To_ImGui_Keybinds(int key);

//Update Functions
void Update_Mouse_Details(GLFWwindow* window);
void Update_Mouse_Cursor(GLFWwindow* window);

//Creation Functions
void ImGui_Input_Setup(GLFWwindow* window);
void ImGui_Input_Loop(GLFWwindow* window);
