#include "../../include/Graphics_Headers/UI.h"

UI::UI(GLFWwindow* window, int windowHeight, int windowWidth, std::vector<std::shared_ptr<Gizmos>> gizmosVec) : _window(window), _windowHeight(windowHeight), _windowWidth(windowWidth), _gizmosVec(gizmosVec)
{ 

}

UI::~UI()
{
	DestroyMenu();
}


void UI::mouse_callback()
{

}

void UI::zoom_callback()
{		
	if(glfwGetKey(_window, GLFW_KEY_I) == GLFW_PRESS)
	{
		yOffset -= 0.25f;
	}

	if(glfwGetKey(_window, GLFW_KEY_O) == GLFW_PRESS)
	{
		yOffset += 0.25f;
	}
}


void UI::SetupMenu()
{
	//Create Some Settings with the Menu and Setup the Context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	
	ImGui_Input_Setup(_window);

	// Flag Settings that User Can Set
	if(darkMode)
		ImGui::StyleColorsDark();
	else
		ImGui::StyleColorsLight();

	// Flag Settings that User Can Set

	ImGui_ImplOpenGL3_Init("#version 330");
}

void UI::MenuLoop()
{

	io = &ImGui::GetIO();
	
	//Find a Difference in Time
	float time = (float)glfwGetTime();
	io->DeltaTime = time - lastTime;
	lastTime = time;

	ImGui_ImplOpenGL3_NewFrame();

	//Handle the Input for ImGui which runs loops of callbacks
	ImGui_Input_Loop(_window);

	int tempW, tempH;
	int displayW, displayH;
	//Get Information About the Window to set up the menu correctly
	glfwGetWindowSize(_window, &tempW, &tempH);
	glfwGetFramebufferSize(_window, &displayW, &displayH);
	io->DisplaySize = ImVec2((float)tempW, (float)tempH);
	
	if(tempW > 0 && tempH > 0)
		io->DisplayFramebufferScale = ImVec2((float)displayW / tempW, (float)displayH / tempH);
	
	ImGui::NewFrame();

	//Set the position and size for the bottom bar in relation to screen size
	ImGui::SetWindowPos("Bottom bar", ImVec2(0.0f, (float)tempH - float(tempH / 4)));
	ImGui::SetWindowSize("Bottom bar", ImVec2((float)(tempW/2), (float)(tempH / 2)));
	
	//Creation of our own window always starts with Begin()
	static bool show{true};
	ImGui::Begin("Bottom bar", &show, io->ConfigFlags);
	//With the bottom dockable bar we want access to things such as the Gizmos and Imports
	int val;

	ImGui::Text("Hello World!");
	ImGui::Text("Going to Need Space for all our objects and stuff");
	ImGui::InputInt("Bob",&val );

	ImGui::End();
	//Creation of our own window always ends with End()

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	mouse_callback();
	zoom_callback();

}


void UI::MenuEventHandler()
{

}

void UI::DestroyMenu()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
}
