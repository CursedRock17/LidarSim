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

	//Set the position and size for the Gizmos List
	ImGui::SetWindowPos("Gizmos list", ImVec2((float)(tempW - (tempW / 3)), 0.0f));
	ImGui::SetWindowSize("Gizmos list", ImVec2((float)tempW / 6.0f, (float)tempH - (tempH / 4.0f)));

	//Set the position and size for the sidebar
	ImGui::SetWindowPos("Side bar", ImVec2((float)(tempW - (tempW / 6)), 0.0f));
	ImGui::SetWindowSize("Side bar", ImVec2((float)tempW / 2.0f, (float)tempH));

	//Create the Scene window at the origin and take up the rest of the space
	sceneWidth = float(tempW - (tempW / 3));
	sceneHeight = float(tempH - (tempH / 4));

	//Creation of our own window always starts with Begin()
	ImGui::Begin("Bottom bar", &show, io->ConfigFlags);
	//With the bottom dockable bar we want access to things such as the Gizmos and Imports

	ImGui::Text("Hello World!");
	
	//Create a button in an if statement to use as an on click
	if(ImGui::Button("Create\nCube", ImVec2(ImGui::GetWindowWidth() / 10.0f, ImGui::GetWindowHeight() / 5.0f)))
	{
		_GraphicsRef->CreateCube();
	}
	
	if(ImGui::Button("Create\nPyramid", ImVec2(ImGui::GetWindowWidth() / 10.0f, ImGui::GetWindowHeight() / 5.0f)))
	{
		_GraphicsRef->CreatePyramid();
	}


	ImGui::End();
	//Creation of our own window always ends with End()
	
	//Element for Each Control Panel for the GizmoUIs which we can make a lamba to keep context
	auto ControlPanelUI = [&](std::shared_ptr<Gizmos> CurrentGizmosRef){
		// This Control Panel will be able to control the entirety of the object within all the systems
		// First it should be able to control the Gizmo's Rotation, Scale, Transform : All the physical Things
		// It should also house the scripts on it depending on if it's an electronic or robot or whatever
		// It can control both the physics and electricity of the object

		auto StringResizeCallback = [=](ImGuiInputTextCallbackData* data) ->std::string {
			//CurrentGizmosRef->objectName.resize(data->BufSize);

			//data->Buf = CurrentGizmosRef->objectName.begin();
		};

		//Because we're using std::string we need to create a resizing callback ^^
		//ImGui::InputText("Name: ", CurrentGizmosRef->objectName.begin(), io->ConfigFlags, StringResizeCallback);

		//Rotation Setter
		float* x_rotate = &CurrentGizmosRef->GetRotation()[0];
		float* y_rotate = &CurrentGizmosRef->GetRotation()[1];
		float* z_rotate = &CurrentGizmosRef->GetRotation()[2];

		ImGui::Text("Rotation");
		ImGui::InputFloat("X_Rotation: ", x_rotate);
		ImGui::InputFloat("Y_Rotation: ", y_rotate);
		ImGui::InputFloat("Z_Rotation: ", z_rotate);

		CurrentGizmosRef->SetRotation(*x_rotate, *y_rotate, *z_rotate);
		//Translation Setter
		float* x_translate = &CurrentGizmosRef->GetTranslation()[0];
		float* y_translate = &CurrentGizmosRef->GetTranslation()[1];
		float* z_translate = &CurrentGizmosRef->GetTranslation()[2];
		
		ImGui::Text("Translation");
		ImGui::InputFloat("X_Translation: ", x_translate);
		ImGui::InputFloat("Y_Translation: ", y_translate);
		ImGui::InputFloat("Z_Translation: ", z_translate);

		CurrentGizmosRef->SetTranslation(*x_translate, *y_translate, *z_translate);
		//Scale Setter
		float* x_scale = &CurrentGizmosRef->GetScale()[0];
		float* y_scale = &CurrentGizmosRef->GetScale()[1];
		float* z_scale = &CurrentGizmosRef->GetScale()[2];

		ImGui::Text("Scale");
		ImGui::InputFloat("X_Scale: ", x_scale);
		ImGui::InputFloat("Y_Scale: ", y_scale);
		ImGui::InputFloat("Z_Scale: ", z_scale);

		CurrentGizmosRef->SetScale(*x_scale, *y_scale, *z_scale);
		//Color Setter
		float* red_col = &CurrentGizmosRef->GetColor()[0];
		float* green_col = &CurrentGizmosRef->GetColor()[1];
		float* blue_col = &CurrentGizmosRef->GetColor()[2];

		ImGui::Text("Color");
		ImGui::InputFloat("Red_col: ", red_col);
		ImGui::InputFloat("Green_col: ", green_col);
		ImGui::InputFloat("Blue_col: ", blue_col);

		CurrentGizmosRef->SetColor(*red_col, *green_col, *blue_col);


	};


	ImGui::Begin("Gizmos list", &show, io->ConfigFlags);
	/* Create a Sidebar where we have both the list of all the Gizmos in the application, each of these will be interactable
	 * so on double click or clicking on the object thorugh implemenation of physics system, we will be able to control everything
	 * on that object using a specialized Gizmo UI defined in UI. The only way to do this is via looping through all of the Application Gizmos
	 * but may be able to skip useless objects
	 */
	
	for(const auto& GizmoUI : _gizmosVec)
	{
		//Loop and Render Each Gizmo as an interacble level
		if(ImGui::Selectable(GizmoUI->objectName.c_str())){
			activeGizmo = GizmoUI;
		}
	}
	ImGui::End();

	//Creation of Sidebar
	ImGui::Begin("Side bar", &show, io->ConfigFlags);
	
	// --- Description of Sidebar UI --- // 
	/* This will be where the control panel sits when activated which will allow the user to set position, color, scripts, access to different abilities that the Gizmo can actually do, etc.
	 *
	 *
	 *
	 */
	
	if(activeGizmo){
		ImGui::Text("%s", activeGizmo->objectName.c_str());
		ControlPanelUI(activeGizmo);
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

