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
	//Controls for Rotating the Camera - In order to do so we need to check the position of the mouse -- we also check if the mouse is our window
	if(sceneFocused){
		if(ImGui::IsMouseDown(ImGuiMouseButton_Left)){
			_GraphicsRef->RotateCam(static_cast<float>(io->MousePos.x), static_cast<float>(io->MousePos.y), true);
		}
		else {
			//Only need to reset the first touch if we are not actively moving
			_GraphicsRef->RotateCam(static_cast<float>(io->MousePos.x), static_cast<float>(io->MousePos.y), false);
		}	
	} else {
			_GraphicsRef->RotateCam(static_cast<float>(io->MousePos.x), static_cast<float>(io->MousePos.y), false);
	}
}	

void UI::accept_input(std::shared_ptr<Graphics> _GraphicsRef)
{
	//Utilize these keybinds if we are on the main scene (simulation Graphics)
	if(sceneFocused){
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

	//Zoom Callback In Scene
	if(ImGui::IsKeyPressed(ImGuiKey_I)){
		_GraphicsRef->ZoomCam(true);	
	}
	else if(ImGui::IsKeyPressed(ImGuiKey_O)){
		_GraphicsRef->ZoomCam(false);
	}
	//Zoom Callback In Scene
   }
}

void UI::ImGuiContextLoop()
{
	//All of this information has to be processed for every UI setting that deals with imgui which simply processes out the current window
	io = &ImGui::GetIO();
	
	//Find a Difference in Time
	time = (float)glfwGetTime();
	io->DeltaTime = time - lastTime;
	lastTime = time;

	//Handle the Input for ImGui which runs loops of callbacks
	ImGui_Input_Loop(_window);

	//Get Information About the Window to set up the menu correctly
	glfwGetWindowSize(_window, &tempW, &tempH);
	glfwGetFramebufferSize(_window, &displayW, &displayH);
	io->DisplaySize = ImVec2((float)tempW, (float)tempH);
	
	if(tempW > 0 && tempH > 0)
		io->DisplayFramebufferScale = ImVec2((float)displayW / tempW, (float)displayH / tempH);
}

void UI::SetupMenu()
{
	//Create Some Settings with the Menu and Setup the Context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	io = &ImGui::GetIO();
	//Setup Flags so that we can more easily customize our imgui menu
	io->ConfigFlags |= ImGuiWindowFlags_NoTitleBar;
	io->ConfigFlags |= ImGuiWindowFlags_NoFocusOnAppearing;


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
	ImGuiContextLoop();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();
	
	mouse_callback(_GraphicsRef);
	accept_input(_GraphicsRef);

	//Set the position and size for the bottom bar in relation to screen size
	ImGui::SetWindowPos("Bottom bar", ImVec2(0.0f, (float)tempH - float(tempH / 4)));
	ImGui::SetWindowSize("Bottom bar", ImVec2((float)(tempW - (tempW / 6)), (float)(tempH / 2.0f)));

	//Set the position and size for the sidebar
	ImGui::SetWindowPos("Side bar", ImVec2((float)(tempW - (tempW / 6)), 0.0f));
	ImGui::SetWindowSize("Side bar", ImVec2((float)tempW / 2.0f, (float)tempH));

	//Create the Scene window at the origin and take up the rest of the space
	sceneWidth = float(tempW - (tempW / 6));
	sceneHeight = float(tempH - (tempH / 4));

	//Creation of our own window always starts with Begin()
	ImGui::Begin("Bottom bar", &show, io->ConfigFlags);
	//With the bottom dockable bar we want access to things such as the Gizmos and Imports

	ImGui::Text("Hello World!");
	
	//Create a button in an if statement to use as an on click
	if(ImGui::Button("Create \n Cube", ImVec2(ImGui::GetWindowWidth() / 10.0f, ImGui::GetWindowHeight() / 5.0f)))
	{
		_GraphicsRef->CreateCube();
	}
	
	if(ImGui::Button("Create \n Pyramid", ImVec2(ImGui::GetWindowWidth() / 10.0f, ImGui::GetWindowHeight() / 5.0f)))
	{
		_GraphicsRef->CreatePyramid();
	}


	ImGui::End();
	//Creation of our own window always ends with End()

	//Creation of Sidebar
	ImGui::Begin("Side bar", &show, io->ConfigFlags);

	char buffer;

	ImGui::InputText("Texty", &buffer, 256);

	for(int i = 0; i < 5; i++)
	{
		ImGui::Text("Bob");
	}

	ImGui::End();
	//End of Sidebar

	ImGui::SetWindowPos("Main scene", ImVec2(0.0f, 0.0f));
	ImGui::SetWindowSize("Main scene", ImVec2(sceneWidth, sceneHeight));

	//Creation of our own window always starts with Begin()
	//Get the remaining space of the screen and fill it with the scene
	ImGui::Begin("Main scene", &show, io->ConfigFlags);

	// Need to utilize this if/else pairing to find out what control to use for the main scene, as we would run into input issues - This also prevents us from having to create another context
	if(ImGui::IsWindowFocused())
	{
		sceneFocused = true;
	}
	else {
		sceneFocused = false;
	}

	ImGui::Image((ImTextureID)RTO, ImVec2(sceneWidth - 10.0f, sceneHeight - 32.5f));

	ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	
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

