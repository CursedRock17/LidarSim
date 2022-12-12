#include "../../include/Graphics_Headers/UI.h"
#include <iostream>

UI::UI(GLFWwindow* window, int windowHeight, int windowWidth) : _window(window), _windowHeight(windowHeight), _windowWidth(windowWidth)
{

}

UI::~UI()
{
	DestroyMenu();
}

void UI::SetupMenu()
{
	//Create Some Settings with the Menu and Setup the Context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	
	//Have to create this context in order to utilize imgui
	io = &ImGui::GetIO();
	
	// Flag Settings that User Can Set
	if(darkMode)
		ImGui::StyleColorsDark();
	else
		ImGui::StyleColorsLight();

	// Flag Settings that User Can Set
    // NonUserSet settings:
        io->BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
        io->BackendFlags |= ImGuiBackendFlags_HasSetMousePos;          // We can honor io.WantSetMousePos requests (optional, rarely used)

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


	ImGui_ImplOpenGL3_Init("#version 330");
}

void UI::MenuLoop()
{

	io = &ImGui::GetIO();
	io->DisplaySize = ImVec2((float)_windowWidth, (float)_windowHeight);
	
	//Find a Difference in Time
	float time = (float)glfwGetTime();
	io->DeltaTime = time - lastTime;
	lastTime = time;
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();
	
	static bool show = true;
	ImGui::ShowDemoWindow(&show);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::DestroyMenu()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
}
