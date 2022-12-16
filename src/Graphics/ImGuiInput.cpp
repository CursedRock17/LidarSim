#include "../../include/Graphics_Headers/ImGuiInput.h"
#include <iostream>


//Creation of Callback Identifiers
GLFWmousebuttonfun mouse_button_fun = nullptr;
GLFWcharfun char_fun = nullptr;
GLFWkeyfun key_fun = nullptr;
GLFWscrollfun scroll_fun = nullptr;
GLFWcursorposfun cursor_pos_fun = nullptr;

//Have to create this context in order to utilize imgui
ImGuiIO* io;
double cursorX{400.0f};
double cursorY{300.0f};

//Callback Functions
void ImGui_Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset)
{
	io = &ImGui::GetIO();
	//Move the screen based on the scroll value
	io->MouseWheel += (float)yoffset;
	io->MouseWheelH += (float)xoffset;
}

void ImGui_Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS){
		io->KeysDown[scancode] = true;
	}
	else if(action == GLFW_RELEASE){
		io->KeysDown[scancode] = false;
	}
}

void ImGui_Mouse_Button_Callback(GLFWwindow* window, int button, int action, int mods)
{
	io = &ImGui::GetIO();

	if(action == GLFW_PRESS){
		io->MouseDown[button] = true;
	}
	if(action == GLFW_RELEASE){
		io->MouseDown[button] = false;
	}
}


void ImGui_Cursor_Pos_Callback(GLFWwindow* window, double xpos, double ypos)
{
	cursorX = xpos;
	cursorY = ypos;
}

void ImGui_Char_Callback(GLFWwindow* window, unsigned int codepoint)
{
	io = &ImGui::GetIO();
	io->AddInputCharacter(codepoint);
}

//Update Functions
void Update_Mouse_Details(GLFWwindow* window)
{
	io = &ImGui::GetIO();
	//Update Position and Buttons
	io->MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
	const bool focused = glfwGetWindowAttrib(window, GLFW_FOCUSED) != 0;

	if(focused)
	{
		double mouse_x, mouse_y;
		glfwGetCursorPos(window, &mouse_x, &mouse_y);
		io->MousePos = ImVec2((float)mouse_x, (float)mouse_y);

	}

}

void Update_Mouse_Cursor(GLFWwindow* window)
{
	io = &ImGui::GetIO();

	ImGuiMouseCursor mouse_cursor = ImGui::GetMouseCursor();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

//Creation Functions
void ImGui_Input_Setup(GLFWwindow* window)
{
	io = &ImGui::GetIO();

	// NonUserSet settings:
        io->ConfigFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
        io->ConfigFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)

    // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
        io->KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io->KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io->KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io->KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io->KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io->KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io->KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io->KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io->KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io->KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io->KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io->KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io->KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io->KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io->KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io->KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
        io->KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io->KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io->KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io->KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io->KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io->KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
	

	//Setup all the callbacks with our functions
	mouse_button_fun = glfwSetMouseButtonCallback(window, ImGui_Mouse_Button_Callback);
	char_fun = glfwSetCharCallback(window, ImGui_Char_Callback);
	key_fun = glfwSetKeyCallback(window, ImGui_Key_Callback);
	scroll_fun = glfwSetScrollCallback(window, ImGui_Scroll_Callback);
	cursor_pos_fun = glfwSetCursorPosCallback(window, ImGui_Cursor_Pos_Callback);


}

void ImGui_Input_Loop(GLFWwindow* window)
{
	io = &ImGui::GetIO();

	Update_Mouse_Details(window);
	Update_Mouse_Cursor(window);

}
