#include "../../include/Graphics_Headers/UI.h"
#include <ctime>
#include <iostream>

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

void UI::accept_input(std::shared_ptr<Graphics> _GraphicsRef)
{
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
}


void UI::MenuLoop(std::shared_ptr<Graphics> _GraphicsRef, std::string* application_mode)
{
}


bool UI::ImGui_InputText(const char* label, std::string* str, ImGuiInputTextFlags flags)
{
	//This function is created in reference to the ImGui docs stating overload functions for std::string compared to const char* due to resizing capabillities check: https://github.com/ocornut/imgui/blob/docking/misc/cpp/imgui_stdlib.h for more details
	IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
	return ImGui::InputText(label, str->data(), (size_t)64, flags, StringResizeCallback, (void*)str);
}

int UI::StringResizeCallback(ImGuiInputTextCallbackData* data)
{
	if(data->EventFlag == ImGuiInputTextFlags_CallbackResize){
		std::string* str = (std::string*)data->UserData;
		IM_ASSERT(str->data() == data->Buf);
		str->resize(data->BufSize);

		data->Buf = str->data();
	}
	return 0;
}

void UI::DestroyMenu()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
}



void UI::SetupStyles()
{
	style = &ImGui::GetStyle();
	style->Colors[ImGuiCol_Text]                  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled]          = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	style->Colors[ImGuiCol_WindowBg]              = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	style->Colors[ImGuiCol_ChildBg]               = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style->Colors[ImGuiCol_PopupBg]               = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style->Colors[ImGuiCol_Border]                = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	style->Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_FrameBg]               = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	style->Colors[ImGuiCol_TitleBg]               = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	style->Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	style->Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	style->Colors[ImGuiCol_CheckMark]             = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	style->Colors[ImGuiCol_SliderGrab]            = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	style->Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
	style->Colors[ImGuiCol_Button]                = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive]          = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	style->Colors[ImGuiCol_Header]                = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive]          = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	style->Colors[ImGuiCol_Separator]             = style->Colors[ImGuiCol_Border];
	style->Colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
	style->Colors[ImGuiCol_SeparatorActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	style->Colors[ImGuiCol_ResizeGrip]            = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
	style->Colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	style->Colors[ImGuiCol_Tab]                   = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
	style->Colors[ImGuiCol_TabHovered]            = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
	style->Colors[ImGuiCol_TabActive]             = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
	style->Colors[ImGuiCol_TabUnfocused]          = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style->Colors[ImGuiCol_DockingPreview]        = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
	style->Colors[ImGuiCol_DockingEmptyBg]        = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style->Colors[ImGuiCol_PlotLines]             = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	style->Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	style->Colors[ImGuiCol_DragDropTarget]        = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	style->Colors[ImGuiCol_NavHighlight]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style->Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	style->Colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	style->Colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	style->GrabRounding                           = style->FrameRounding = 2.5f;
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


// Start of MainUI Class
MainUI::MainUI(GLFWwindow* window, int windowHeight, int windowWidth, std::vector<std::shared_ptr<Gizmos>> gizmosVec) : UI(window, windowHeight, windowWidth, gizmosVec)
{

}

MainUI::~MainUI()
{
	//Should be default because it will call base classes destructor
}


void MainUI::mouse_callback(std::shared_ptr<Graphics> _GraphicsRef)
{
	//Controls for Rotating the Camera - In order to do so we need to check the position of the mouse -- we also check if the mouse is our window
	if(sceneFocused){
		if(ImGui::IsMouseDown(ImGuiMouseButton_Left)){
            if(ImGui::IsKeyDown(ImGuiKey_LeftCtrl)){
			_GraphicsRef->RotateCam(static_cast<float>(io->MousePos.x), static_cast<float>(io->MousePos.y), true);
            } //Now Handle Input for Object selection
            else {
            _GraphicsRef->SelectGizmo(static_cast<float>(io->MousePos.x), static_cast<float>(io->MousePos.y));
            }

		}
		else {
			//Only need to reset the first touch if we are not actively moving
			_GraphicsRef->RotateCam(static_cast<float>(io->MousePos.x), static_cast<float>(io->MousePos.y), false);
		}
	} else {
			_GraphicsRef->RotateCam(static_cast<float>(io->MousePos.x), static_cast<float>(io->MousePos.y), false);
	}
}

void MainUI::accept_input(std::shared_ptr<Graphics> _GraphicsRef)
{
	//Utilize these keybinds if we are on the main scene (simulation Graphics)
	if(sceneFocused){
	//Directions Input
	// Utilize the Directions enum to provide specific detail of where to move then use the Graphics Ref to manipulate the camera

	// Move Forward
	if(ImGui::IsKeyPressed(ImGuiKey_W) || ImGui::IsKeyPressed(ImGuiKey_UpArrow)){
		//Limited Keys so use shift to control y axis
		if(ImGui::IsKeyDown(ImGuiKey_LeftShift)){
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
		if(ImGui::IsKeyDown(ImGuiKey_LeftShift)){
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

void MainUI::ControlPanelUI(std::shared_ptr<Gizmos> CurrentGizmosRef, std::shared_ptr<Graphics> GraphicsRef)
{
		// This Control Panel will be able to control the entirety of the object within all the systems
		// First it should be able to control the Gizmo's Rotation, Scale, Transform : All the physical Things
		// It should also house the scripts on it depending on if it's an electronic or robot or whatever
		// It can control both the physics and electricity of the object

		//Because we're using std::string we need to create a resizing callback ^^
		ImGui_InputText("Name: ", &CurrentGizmosRef->objectName);
		ImGui::Separator();

        CurrentGizmosRef->GizmosUILoop();

		ImGui::Separator();
		//* This is the Textures part of the UI *//
		//Folder.SetupWindow();


		ImGui::Separator();

		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1, 0, 0, 0.45));
		//Create a Delete Handler
		if(ImGui::Button("Delete"))
		{
			activeGizmo = nullptr;
			GraphicsRef->DeleteGizmo(CurrentGizmosRef->ID);
		}
		ImGui::PopStyleColor();
		ImGui::SameLine();

		if(ImGui::Button("Duplicate")){
			GraphicsRef->DuplicateGizmo(CurrentGizmosRef->ID);
		}

	};


void MainUI::MenuLoop(std::shared_ptr<Graphics> _GraphicsRef, std::string* application_mode)
{
	// ^^ Passing GraphicsRef because we need a reference to the Graphics in order to deal with input but we have to change features within that object instead of being able to create a copy
	ImGuiContextLoop();
	SetupStyles();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	mouse_callback(_GraphicsRef);
	accept_input(_GraphicsRef);
	//Set the position and size for the Top bar in relation to screen size
	ImGui::SetWindowPos("Top bar", ImVec2(0.0f, 0.0f));
	ImGui::SetWindowSize("Top bar", ImVec2((float)(tempW - (tempW / 3.0f)), 25.0f));

	//Set the position and size for the bottom bar in relation to screen size
	ImGui::SetWindowPos("Bottom bar", ImVec2(0.0f, (float)tempH - float(tempH / 4.6f)));
	ImGui::SetWindowSize("Bottom bar", ImVec2((float)(tempW - (tempW / 4.0f)), (float)(tempH / 4.0f)));

	//Set the position and size for the Gizmos List
	ImGui::SetWindowPos("Gizmos list", ImVec2((float)(tempW - (tempW / 3.0f)), 0.0f));
	ImGui::SetWindowSize("Gizmos list", ImVec2((float)tempW / 12.0f, (float)tempH - (tempH / 4.6f)));

	//Set the position and size for the sidebar
	ImGui::SetWindowPos("Side bar", ImVec2((float)(tempW - (tempW / 4.0f)), 0.0f));
	ImGui::SetWindowSize("Side bar", ImVec2((float)tempW / 4.0f, (float)tempH));

	//Create the Scene window at the origin and take up the rest of the space
	sceneWidth = float(tempW - (tempW / 3.0f));
	sceneHeight = float(tempH - (tempH / 4.6f) - 25.0f);

	//Creation of our own window always starts with Begin()
	ImGui::Begin("Bottom bar", &show, io->ConfigFlags);
	//With the bottom dockable bar we want access to things such as the Gizmos and Imports

	//Have to run an additional instance of the Setup for all folder actions
	Folder.SetupWindow("MainFolder");

	ImGui::Text("Component Access");

	//Create a button in an if statement to use as an on click
	if(ImGui::Button("Create\nCube", ImVec2(ImGui::GetWindowWidth() / 10.0f, ImGui::GetWindowHeight() / 5.0f)))
	{
		_GraphicsRef->CreateCube();
	}

	ImGui::SameLine();

	if(ImGui::Button("Create\nPyramid", ImVec2(ImGui::GetWindowWidth() / 10.0f, ImGui::GetWindowHeight() / 5.0f)))
	{
		_GraphicsRef->CreatePyramid();
	}

	ImGui::SameLine();

	if(ImGui::Button("Create\nLight", ImVec2(ImGui::GetWindowWidth() / 10.0f, ImGui::GetWindowHeight() / 5.0f)))
	{
		_GraphicsRef->CreateLight();
	}

	if(ImGui::Button("Import\nModel", ImVec2(ImGui::GetWindowWidth() / 10.0f, ImGui::GetWindowHeight() / 5.0f)))
	{
		//This one needs a folder finder which can push the file as a Gizmo
		ImGui::OpenPopup("MainFolder");
	}

	if(ImGui::Button("Set Model")){
		_GraphicsRef->ImportCustomGizmo(Folder.GetTargetPath());
	}

	ImGui::End();
	//Creation of our own window always ends with End()


	//* End of Textures Changing in UI *//

	ImGui::Begin("Gizmos list", &show, io->ConfigFlags);
	/* Create a Sidebar where we have both the list of all the Gizmos in the application, each of these will be interactable
	 * so on double click or clicking on the object thorugh implemenation of physics system, we will be able to control everything
	 * on that object using a specialized Gizmo UI defined in UI. The only way to do this is via looping through all of the Application Gizmos
	 * but may be able to skip useless objects
	 */

	for(const auto& GizmoUI : _gizmosVec)
	{
		ImGui::PushID(GizmoUI->ID);
		//Loop and Render Each Gizmo as an interacble level
		if(ImGui::Selectable(GizmoUI->objectName.c_str()) ){
			activeGizmo = GizmoUI;
		}
		ImGui::PopID();
	}
	ImGui::End();

	//Creation of top Bar - Contains many controls over the scene like play and pause
	ImGui::Begin("Top bar", &show, io->ConfigFlags);

	if(ImGui::Button("Create"))
	{
		std::string temp = "Create";
		application_mode = &temp;
	}

	ImGui::SameLine();

	if(ImGui::Button("Simulate"))
	{
		std::string temp = "Simulate";
		application_mode = &temp;
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
		ControlPanelUI(activeGizmo, _GraphicsRef);
	}

	ImGui::End();
	//End of Sidebar

	ImGui::SetWindowPos("Main scene", ImVec2(0.0f, 30.0f));
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

	ImGui::Image((ImTextureID)RTO, ImVec2(sceneWidth, sceneHeight - 10.0f));

	ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MainUI::SetupMenu()
{
	//Create Some Settings with the Menu and Setup the Context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	io = &ImGui::GetIO();
	//Setup Flags so that we can more easily customize our imgui menu
	io->ConfigFlags |= ImGuiWindowFlags_NoTitleBar;
	io->ConfigFlags |= ImGuiWindowFlags_NoFocusOnAppearing;


	ImGui_Input_Setup(_window);
	SetupStyles();

	// Flag Settings that User Can Set
	if(darkMode)
		ImGui::StyleColorsDark();
	else
		ImGui::StyleColorsLight();
	// Flag Settings that User Can Set

	ImGui_ImplOpenGL3_Init("#version 330");
}
