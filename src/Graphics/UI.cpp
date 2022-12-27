#include "../../include/Graphics_Headers/UI.h"

UI::UI(GLFWwindow* window, int windowHeight, int windowWidth, std::vector<std::shared_ptr<Gizmos>> gizmosVec) : _window(window), _windowHeight(windowHeight), _windowWidth(windowWidth), _gizmosVec(gizmosVec)
{ 

}

UI::~UI()
{
	DestroyMenu();
}


void UI::mouse_callback(std::shared_ptr<Graphics> _GraphicsRef)
{
}

void UI::zoom_callback(std::shared_ptr<Graphics> _GraphicsRef)
{	
}

void UI::accept_input(std::shared_ptr<Graphics> _GraphicsRef)
{
}

void UI::SetupMenu()
{
	//Create Some Settings with the Menu and Setup the Context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	io = &ImGui::GetIO();
	//Setup Flags so that we can more easily customize our imgui menu
	io->ConfigFlags |= ImGuiWindowFlags_NoTitleBar;

	ImGui_Input_Setup(_window);

	// Flag Settings that User Can Set
	if(darkMode)
		ImGui::StyleColorsDark();
	else
		ImGui::StyleColorsLight();

	// Flag Settings that User Can Set

	ImGui_ImplOpenGL3_Init("#version 330");
}

void UI::MenuLoop(std::shared_ptr<Graphics> _GraphicsRef)
{
	// ^^ Passing GraphicsRef because we need a reference to the Graphics in order to deal with input but we have to change features within that object instead of being able to create a copy
	io = &ImGui::GetIO();
	
	//Find a Difference in Time
	time = (float)glfwGetTime();
	io->DeltaTime = time - lastTime;
	lastTime = time;

	ImGui_ImplOpenGL3_NewFrame();

	//Handle the Input for ImGui which runs loops of callbacks
	ImGui_Input_Loop(_window);

	//Get Information About the Window to set up the menu correctly
	glfwGetWindowSize(_window, &tempW, &tempH);
	glfwGetFramebufferSize(_window, &displayW, &displayH);
	io->DisplaySize = ImVec2((float)tempW, (float)tempH);
	
	if(tempW > 0 && tempH > 0)
		io->DisplayFramebufferScale = ImVec2((float)displayW / tempW, (float)displayH / tempH);
	
	ImGui::NewFrame();

	//Set the position and size for the bottom bar in relation to screen size
	ImGui::SetWindowPos("Bottom bar", ImVec2(0.0f, (float)tempH - float(tempH / 6)));
	ImGui::SetWindowSize("Bottom bar", ImVec2((float)(tempW - (tempW / 6)), (float)(tempH / 2.0f)));

	//Set the position and size for the sidebar
	ImGui::SetWindowPos("Side bar", ImVec2((float)(tempW - (tempW / 6)), 0.0f));
	ImGui::SetWindowSize("Side bar", ImVec2((float)tempW / 2.0f, (float)tempH));

	//Create the Scene window at the origin and take up the rest of the space
	
	sceneWidth = float(tempW - (tempW / 6));
	sceneHeight = float(tempH - (tempH / 6));

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

	char buffer;

	ImGui::InputText("Texty", &buffer, 256);

	ImGui::End();
	//End of Sidebar

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	mouse_callback(_GraphicsRef);
	zoom_callback(_GraphicsRef);
	
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




// ******** Polymorphed Class : SceneUI ********** //

SceneUI::SceneUI(GLFWwindow* window, int windowHeight, int windowWidth, std::vector<std::shared_ptr<Gizmos>> gizmosVec) : UI(window, windowHeight, windowWidth, gizmosVec)
{ 
}

SceneUI::~SceneUI()
{
	//Default Constructor Here because we already make a copy of a UI which deletes itself
}

void SceneUI::SetupMenu()
{
	//Create Some Settings with the Menu and Setup the Context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	io = &ImGui::GetIO();
	//Setup Flags so that we can more easily customize our imgui menu
	//io->ConfigFlags |= ImGuiWindowFlags_NoTitleBar;
	
	ImGui_Input_Setup(_window);

	// Flag Settings that User Can Set
	if(darkMode)
		ImGui::StyleColorsDark();
	else
		ImGui::StyleColorsLight();

	// Flag Settings that User Can Set

	ImGui_ImplOpenGL3_Init("#version 330");
}

void SceneUI::MenuLoop(std::shared_ptr<Graphics> _GraphicsRef)
{
	//This Code Will Mimic the basics of the Regular UI then transform our scene
	io = &ImGui::GetIO();
	
	//Find a Difference in Time
	time = (float)glfwGetTime();
	io->DeltaTime = time - lastTime;
	lastTime = time;

	ImGui_ImplOpenGL3_NewFrame();

	//Handle the Input for ImGui which runs loops of callbacks
	ImGui_Input_Loop(_window);

	//Get Information About the Window to set up the menu correctly
	glfwGetWindowSize(_window, &tempW, &tempH);
	glfwGetFramebufferSize(_window, &displayW, &displayH);
	io->DisplaySize = ImVec2((float)tempW, (float)tempH);
	
	if(tempW > 0 && tempH > 0)
		io->DisplayFramebufferScale = ImVec2((float)displayW / tempW, (float)displayH / tempH);

	
	//Setup scene sizing
	sceneWidth = float(tempW - (tempW / 6));
	sceneHeight = float(tempH - (tempH / 6));
	
	//Has to be included in here
	static bool show{true};

	//Begin the Creation of a window which encases frame in NewFrame and Render
	ImGui::NewFrame();

	ImGui::SetWindowPos("Main scene", ImVec2(0.0f, 0.0f));
	ImGui::SetWindowSize("Main scene", ImVec2(sceneWidth, sceneHeight));

	//Creation of our own window always starts with Begin()

	//Get the remaining space of the screen and fill it with the scene
	ImGui::Begin("Main scene", &show, io->ConfigFlags);

	ImGui::Image((void*)RTO, ImVec2(sceneWidth - 10.0f, sceneHeight - 35.0f));

	ImGui::End();
	//Creation of our own window always ends with End()

        ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	accept_input(_GraphicsRef);
	mouse_callback(_GraphicsRef);
	zoom_callback(_GraphicsRef);
}

void SceneUI::mouse_callback(std::shared_ptr<Graphics> _GraphicsRef)
{
	//Controls for Rotating the Camera - In order to do so we need to check the position of the mouse -- we also check if the mouse is our window
	if(io->WantCaptureMouse){
		if(ImGui::IsMouseDown(ImGuiMouseButton_Left)){
			_GraphicsRef->RotateCam(static_cast<float>(io->MousePos.x), static_cast<float>(io->MousePos.y), true);
		}
	    } 
	else {
			_GraphicsRef->RotateCam(static_cast<float>(io->MousePos.x), static_cast<float>(io->MousePos.y), false);
	}	
}

void SceneUI::accept_input(std::shared_ptr<Graphics> _GraphicsRef)
{
	//As usual wrap everything in our capture to see if we're on the window
	
	if(io->WantCaptureKeyboard){
	//Directions Input
	// Utilize the Directions enum to provide specific detail of where to move then use the Graphics Ref to manipulate the camera
	
	// Move Forward
	if(ImGui::IsKeyPressed(ImGuiKey_W) || ImGui::IsKeyPressed(ImGuiKey_UpArrow)){
		//Limited Keys so use shift to control y axis
		if(ImGui::IsKeyPressed(ImGuiKey_LeftShift)){
			Directions dir = y_pos;
			_GraphicsRef->MoveCamDirection(dir);
		} else {
			Directions dir = z_pos;
			_GraphicsRef->MoveCamDirection(dir);
		}
	}

	//Move Backward
	if(ImGui::IsKeyPressed(ImGuiKey_S) || ImGui::IsKeyPressed(ImGuiKey_DownArrow)){
		//Limited Keys so use shift to control y axis
		if(ImGui::IsKeyPressed(ImGuiKey_LeftShift)){
			Directions dir = y_neg;
			_GraphicsRef->MoveCamDirection(dir);
		} else {
			Directions dir = z_neg;
			_GraphicsRef->MoveCamDirection(dir);
		}
	}

	//Move Right
	if(ImGui::IsKeyPressed(ImGuiKey_D) || ImGui::IsKeyPressed(ImGuiKey_RightArrow)){
		Directions dir = x_pos;
		_GraphicsRef->MoveCamDirection(dir);
	}
	
	//Move Left
	if(ImGui::IsKeyPressed(ImGuiKey_A) || ImGui::IsKeyPressed(ImGuiKey_LeftArrow)){
		Directions dir = x_neg;
		_GraphicsRef->MoveCamDirection(dir);
	}
	//Directions Input
   }
}

void SceneUI::zoom_callback(std::shared_ptr<Graphics> _GraphicsRef)
{
	if(io->WantCaptureKeyboard){
		if(ImGui::IsKeyPressed(ImGuiKey_I)){
			_GraphicsRef->ZoomCam(true);	
		}
		else if(ImGui::IsKeyPressed(ImGuiKey_O)){
			_GraphicsRef->ZoomCam(false);
		}
	}	
}
// ******** Polymorphed Class : SceneUI ********** //


