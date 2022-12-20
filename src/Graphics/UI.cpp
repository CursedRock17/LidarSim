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

	io = &ImGui::GetIO();
	//io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	//io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

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
	ImGui::SetWindowPos("Bottom bar", ImVec2(0.0f, (float)tempH - float(tempH / 8)));
	ImGui::SetWindowSize("Bottom bar", ImVec2((float)(tempW - (tempW / 8)), (float)(tempH / 2.0f)));

	//Set the position and size for the sidebar
	ImGui::SetWindowPos("Side bar", ImVec2((float)(tempW - (tempW / 8)), 0.0f));
	ImGui::SetWindowSize("Side bar", ImVec2((float)tempW / 2.0f, (float)tempH));

	//Create the Scene window at the origin and take up the rest of the space
	
	float sceneWidth = float(tempW - (tempW / 8));
	float sceneHeight = float(tempH - (tempH / 8));
	
	ImGui::SetWindowPos("Main scene", ImVec2(0.0f, 0.0f));
	ImGui::SetWindowSize("Main scene", ImVec2(sceneWidth, sceneHeight));

	static bool show{true};

	//Creation of our own window always starts with Begin()
	ImGui::Begin("Bottom bar", &show, io->ConfigFlags);
	//With the bottom dockable bar we want access to things such as the Gizmos and Imports

	ImGui::Text("Hello World!");
	ImGui::Text("Going to Need Space for all our objects and stuff");

	ImGui::End();
	//Creation of our own window always ends with End()

	//Creation of Sidebar
	ImGui::Begin("Side bar", &show, io->ConfigFlags);

	ImGui::End();
	//End of Sidebar

	//Get the remaining space of the screen and fill it with the scene
	ImGui::Begin("Main scene", &show, io->ConfigFlags);

	ImGui::Image((void*)RTO , ImVec2(sceneWidth - 10.0f, sceneHeight - 10.0f));

	ImGui::End();


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


void UI::SetGizmosVec(std::vector<std::shared_ptr<Gizmos>> gizmosVec)
{
	//Use this function to update the _gizmosVec every single frame
	_gizmosVec = gizmosVec;
}

void UI::SetRenderedTexture(unsigned int _RTO)
{
	RTO = _RTO;
}

