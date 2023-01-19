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
    std::shared_ptr<Gizmos> floorGizmos = std::make_shared<Gizmos>();
    floorGizmos->CreateFloor();
	floorGizmos->ID = _gizmosVec.size();

	_gizmosVec.emplace_back(floorGizmos);
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
	
	//copiedGizmo->ID = _gizmosVec.size() - 1;
	//copiedGizmo->objectName = copiedGizmo->objectName + " (Copy) ";

	//_gizmosVec.emplace_back(copiedGizmo);
}

/* Additional OpenGL funcitons */

//Simple Object Creation Functions
void Graphics::CreateCube()
{
	std::shared_ptr<Gizmos> cube = std::make_shared<Gizmos>();
	cube->CreateCube();
	cube->ID = _gizmosVec.size();

	_gizmosVec.emplace_back(cube);
}


void Graphics::CreatePyramid()
{
	//Same Logic to the Cube
	std::shared_ptr<Gizmos> pyramid = std::make_shared<Gizmos>();
	pyramid->CreatePyramid();
	pyramid->ID = _gizmosVec.size();

	_gizmosVec.emplace_back(pyramid);
}

void Graphics::CreateLight()
{
	std::shared_ptr<Gizmos> light = std::make_shared<Gizmos>();
	light->CreateLight();
	light->ID = _gizmosVec.size();

	_gizmosVec.emplace_back(light);
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
