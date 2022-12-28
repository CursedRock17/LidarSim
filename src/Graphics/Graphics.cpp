#include "../../include/Graphics_Headers/Graphics.h"

Graphics::Graphics(GLFWwindow* window, int windowWidth, int windowHeight, std::vector<std::shared_ptr<Gizmos>> gizmosVec) : _window(window), _windowWidth(windowWidth), _windowHeight(windowHeight), _gizmosVec(gizmosVec)
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
	if(zoomingIn)
	{
		yOffset -= 0.25f;
	}
	if(!zoomingIn)
	{
		yOffset += 0.25f;
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
	if(dirs == x_pos){
		cameraRef->MoveRight();
	}
	else if(dirs == x_neg){
		cameraRef->MoveLeft();
	}
	
	else if(dirs == y_pos){
		cameraRef->MoveUp();
	}

	else if(dirs == y_neg){
		cameraRef->MoveDown();
	}

	else if(dirs == z_pos){
		cameraRef->MoveForward();
	}

	else if(dirs == z_neg){
		cameraRef->MoveBackward();
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
	
	const char* imgLoc = "./resources/crate.png";
	const char* imgSpecularMap = "./resources/crateSpecular.png";

	std::shared_ptr<Gizmos> light = std::make_shared<Gizmos>();

	//Setting up Each object with the variables it would need
	// This set up currently involves creating a Gizmos Object in the code then adding it to the vector so that all objects will be revealed
	// In order to combat this we may need to add a coroutine where we're in creation mode so that we can toggle the loop

	std::vector<float> vertices = {
        //Location              Colors        Textures        Normals      
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f, 
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,  -1.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f,  -1.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,  -1.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,  -1.0f,  0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  -1.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,  -1.0f,  0.0f, 0.0f,
 
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f, 
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f
	}; 


	// ***** Have to Render the Lights after all the object ********* //
	light->CreateShaders("./resources/shaders/vertexLight.vs", "./resources/shaders/lightFrag.fs");
	light->CreateTextures(11, vertices);
	//Can pass nullptr if you don't have textures to apply
	light->RenderTextures(nullptr, nullptr);
	light->objectName = "Light";
	light->ID = 1;
	light->SetColor(1.0f);
	light->SetScale(0.2f);
	light->SetTranslation(1.0f, 1.0f, -1.0f);

	//Add each Gizmos Object to the vector
	_gizmosVec.emplace_back(light);
	CreateCube();

	//Call Initialization of each Object
	for(auto &gizmos : _gizmosVec)
	{
		gizmos->GizmosInit();
	}
		
	//Setting up the Camera
	cameraRef->createView(_windowWidth, _windowHeight, 45.0f);
}

void Graphics::SimulationLoop()
{
    //Create the infinite Loop that will run the _window
  
    // In this loop rendering order is extremely important going to need to add Layers in application
	//Each Objects Loop function
	for(auto &gizmosRef : _gizmosVec)
	{
		if(gizmosRef->objectName != "Light")
		{
			gizmosRef->GizmosLoop(cameraRef->CameraViewMatrix(), cameraRef->aspect, cameraRef->FOV_, true);
		}
		else 
			gizmosRef->GizmosLoop(cameraRef->CameraViewMatrix(), cameraRef->aspect, cameraRef->FOV_, false);
		
		if(gizmosRef->objectName != "Light"){
			gizmosRef->SetViewPos(cameraRef->GetCameraPosition());
			gizmosRef->BasicMove();
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

	_gizmosVec.emplace_back(cube);
}


void Graphics::CreatePyramid()
{
	//Same Logic to the Cube
	std::shared_ptr<Gizmos> pyramid = std::make_shared<Gizmos>();
	pyramid->CreatePyramid();

	_gizmosVec.emplace_back(pyramid);
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
