#include "../../include/Graphics_Headers/Graphics.h"

Graphics::Graphics(GLFWwindow* window, int windowWidth, int windowHeight, std::vector<std::shared_ptr<Gizmos>> gizmosVec, std::string mode) : _window(window), _windowWidth(windowWidth), _windowHeight(windowHeight), _gizmosVec(gizmosVec), _mode(mode)
{
    RenderingInit();
}

Graphics::~Graphics()
{
    RenderingEnd();
}

void Graphics::RotateCam(float xPosition, float yPosition, bool newClick)
{
	if(newClick) {
		cameraRef->RotateCamera(xPosition, yPosition);
	} else {
		cameraRef->firstClick = true;
	}
}

void Graphics::ZoomCam(bool zoomingIn)
{
	if(zoomingIn) {
		yOffset -= 0.5f;
	} else {
		yOffset += 0.50f;
	}
	//Simple control options to push our perspective closer or further back
	//Now Add some restraints to how it can move

	if(yOffset < 0.0f)
		yOffset = 0.0f;
	else if(yOffset > 45.0f)
		yOffset = 45.0f;

	cameraRef->ZoomCamera(xOffset, yOffset);
}

void Graphics::MoveCamDirection(Directions dirs)
{
	//Utilize the Directions enum to have an understanding of where we need to move the camera, this is just a basic control panel for the scene
	//These directions are labelled so the camera just moves in that direction
	switch(dirs){
		case x_pos: {
			cameraRef->MoveRight();
			break;
		}
		case x_neg: {
			cameraRef->MoveLeft();
			break;
		}
		case y_pos: {
			cameraRef->MoveUp();
			break;
		}
		case y_neg: {
			cameraRef->MoveDown();
			break;
		}
		case z_pos: {
			cameraRef->MoveForward();
			break;
		}
		case z_neg: {
			cameraRef->MoveBackward();
			break;
		}
	}

}

//A multipurpose function that will reverse order of our mouse click in order to return a ray cast
glm::vec3 Graphics::CreateRayCast(float mouse_x, float mouse_y)
{
   //First reverse the viewport coordinates to get range of [-1,1]
   float clip_x = (2.0f * mouse_x) / _windowWidth - 1.0f;
   float clip_y = 1.0f - (2.0f * mouse_y) / _windowHeight;
   // There's no z axis in the 2d screen or clip space
   //Prep Transform from the Clip Space with a 4D matrix that will align with the projection matrix
   glm::vec4 rayClip = glm::vec4(clip_x, clip_y, -1.0f, 1.0f);

   //Now go to the View Space by inverting the projection matrix with the viewport RayClip
   glm::mat4 projectionMatrix = glm::perspective(glm::radians(cameraRef->FOV_), cameraRef->aspect, 0.1f, 100.0f);
   glm::vec4 rayEye = glm::inverse(projectionMatrix) * rayClip;
   rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);

   //Now We can finally move to the world coordinates by inverting the view matrix
   glm::mat4 viewMatrix = cameraRef->CameraViewMatrix();
   glm::vec3 rayWorld = (glm::inverse(viewMatrix) * rayEye);
   rayWorld = glm::normalize(rayWorld);

   return rayWorld;
}

//Handeling Logic for Gizmo Selection
void Graphics::SelectGizmo(float mouse_x, float mouse_y)
{
    //Get the current mouse position from the input which allows us to track and find which object we're on by converting to framebuffer space
    glm::vec3 pickingRay = CreateRayCast(mouse_x, mouse_y);
    glm::vec3 pickedRay = glm::normalize(pickingRay);
   pickedRay += 3;

    //std::cout << pickedRay[0] << " " << pickedRay[1] << " " << pickedRay[2] << std::endl;

    //Read to see what's at the current pixel, to see if it matches with an object
    //float pixels[4];
    //glReadPixels(mouse_x, pickingRay[1] - mouse_y , 1, 1, GL_RGBA, GL_FLOAT, &pixels);
    //std::cout << pixels[0] << " " << pixels[1] << " " << pixels[2] << std::endl;
}

void Graphics::RenderingInit()
{
}

void Graphics::RenderingEnd()
{
}

void Graphics::SimulationSetup()
{
	// -- All the GL Functions -- //

	//These functions allow 3D rendering to be resolved nicely
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_STENCIL_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);

	//Face Culling Will save resources as we don't have to look at some vertices
	// -- All the GL Functions -- //

	//Setting up the Camera
	cameraRef->createView(_windowWidth, _windowHeight, 45.0f);

	//Setting up background objects
	CreateFloor();
}

void Graphics::SimulationLoop()
{
	//Each Gizmos Loop function
	for(const auto &gizmosRef : _gizmosVec)
	{
		gizmosRef->SetViewPos(cameraRef->GetCameraPosition());
		gizmosRef->GizmosLoop(cameraRef->CameraViewMatrix(), cameraRef->aspect, cameraRef->FOV_);

		if(gizmosRef->objectName != "Light"){
			if(_mode == "Simulate")
			{
				//Consistenly change the object in the space while the play button is pressed
				gizmosRef->UpdateGizmoSpace();
			}
		}
		gizmosRef->RenderContainer();
	}
	cameraRef->CameraLoop();
	//Each Objects Loop function
}

void Graphics::RefreshGizmos()
{
	//Use This as a loop in order to render all of the vertices of each object
	for(const auto &gizmosRef : _gizmosVec)
	{
	}
}

void Graphics::DeleteGizmo(int targetID)
{
	bool targetFound{false};
	//Have to linearly find the target we want to delete as its a vector, but after that point we will just condense IDs by 1 less
	for(std::vector<std::shared_ptr<Gizmos>>::iterator iter = _gizmosVec.begin(); iter != _gizmosVec.end();) {
	//Have to use a double pointer on the iterator in order to access the actual object
	if((**iter).ID == targetID) {
			_gizmosVec.erase(iter);
		  	targetFound = true;
	} else {
	        if(targetFound){
			_gizmosVec.at((**iter).ID - 1)->ID = (**iter).ID - 1;
		}
		++iter;
	    }
    }
}

void Graphics::DuplicateGizmo(int targetID)
{
	//Just access and create a copy of the Gizmo (Most likely the one we're on) by creating a new one
	//std::shared_ptr<Gizmos> copiedGizmo = std::make_shared<Gizmos>();
	std::shared_ptr<Gizmos> copiedGizmp = _gizmosVec.at(targetID);

	//copiedGizmo->ID = _gizmosVec.size() - 1;
	//copiedGizmo->objectName = copiedGizmo->objectName + " (Copy) ";

	//_gizmosVec.emplace_back(copiedGizmo);
}

/* Additional OpenGL funcitons */

//Simple Object Creation Functions
void Graphics::CreateCube()
{
	std::shared_ptr<BasicGizmo> cube = std::make_shared<BasicGizmo>();
	cube->CreateCube();
	cube->ID = _gizmosVec.size();

	_gizmosVec.emplace_back(cube);
}


void Graphics::CreatePyramid()
{
	//Same Logic to the Cube
	std::shared_ptr<BasicGizmo> pyramid = std::make_shared<BasicGizmo>();
	pyramid->CreatePyramid();
	pyramid->ID = _gizmosVec.size();

	_gizmosVec.emplace_back(pyramid);
}

void Graphics::CreateLight()
{
	std::shared_ptr<BasicGizmo> light = std::make_shared<BasicGizmo>();
	light->CreateLight();
	light->ID = _gizmosVec.size();

	_gizmosVec.emplace_back(light);
}

void Graphics::CreateFloor()
{
    std::shared_ptr<BasicGizmo> floorGizmos = std::make_shared<BasicGizmo>();
	floorGizmos->CreateFloor();
	floorGizmos->ID = _gizmosVec.size();

	_gizmosVec.emplace_back(floorGizmos);

}

void Graphics::ImportCustomGizmo(const std::string& filePath)
{
	std::shared_ptr<Gizmos> customModel = std::make_shared<Gizmos>();
	//Since importing we have to check to see if it works
	if(customModel->CreateCustomGizmo(filePath)){
		customModel->ID = _gizmosVec.size();
		_gizmosVec.emplace_back(customModel);
		customModel->objectName = "Default";
	}

}

//Simple Object Creation Functions

std::vector<std::shared_ptr<Gizmos>> Graphics::GetGizmosVec()
{
	//Simple Getter Function to refresh every frame for the main application
	return _gizmosVec;
}

void Graphics::SetGizmosVec(std::vector<std::shared_ptr<Gizmos>> gizmosVec)
{
	//Simple Setter Function
	_gizmosVec = gizmosVec;
}

/* Additional OpenGL funcitons */
