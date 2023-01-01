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

	//Face Culling Will save resources as we don't ahve to look at some vertices
	// -- All the GL Functions -- //
	
	//Setting up the Camera
	cameraRef->createView(_windowWidth, _windowHeight, 45.0f);
}

void Graphics::SimulationLoop()
{
    //Create the infinite Loop that will run the _window
  
    // In this loop rendering order is extremely important going to need to add Layers in application
	//Each Objects Loop function
	for(const auto &gizmosRef : _gizmosVec)
	{
		if(gizmosRef->objectName != "Light")
		{
			gizmosRef->GizmosLoop(cameraRef->CameraViewMatrix(), cameraRef->aspect, cameraRef->FOV_, true);
		}
		else 
			gizmosRef->GizmosLoop(cameraRef->CameraViewMatrix(), cameraRef->aspect, cameraRef->FOV_, false);
		
		if(gizmosRef->objectName != "Light"){
			gizmosRef->SetViewPos(cameraRef->GetCameraPosition());
			if(_mode == "Simulate")
			{
				gizmosRef->UpdateGizmoSpace();
			}
			//If we're in the creation mode we can just set everything back to the default to make it only make one change during the frame, equvilent to a one time move

		}
		gizmosRef->RenderContainer();
	}

	cameraRef->CameraLoop();
	//Each Objects Loop function
}

void Graphics::RefreshGizmos()
{
	//Use This as a loop in order to render all of the vertices of each object 
	for(auto &gizmosRef : _gizmosVec)
	{
		gizmosRef->RenderContainer();
	}
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
