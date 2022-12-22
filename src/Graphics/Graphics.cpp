#include "../../include/Graphics_Headers/Graphics.h"

Graphics::Graphics(GLFWwindow* window, int windowWidth, int windowHeight, std::vector<std::shared_ptr<Gizmos>> gizmosVec) : _window(window), _windowWidth(windowWidth), _windowHeight(windowHeight), _gizmosVec(gizmosVec)
{
    RenderingInit();
}

Graphics::~Graphics()
{
    RenderingEnd();
}


void Graphics::mouse_callback()
{
	xPos = _windowWidth / 2;
	yPos = _windowHeight / 2;

	lastXPos = xPos;
	lastYPos = yPos;

	glfwGetCursorPos(_window, &xPos, &yPos);

	if(lastXPos != xPos || lastYPos != yPos){
		if(glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
			cameraRef->RotateCamera(static_cast<float>(xPos), static_cast<float>(yPos));
		} else {
			cameraRef->firstClick = true;
		}
	}
}

void Graphics::zoom_callback()
{		
	if(glfwGetKey(_window, GLFW_KEY_I) == GLFW_PRESS)
	{
		yOffset -= 0.25f;
	}

	if(glfwGetKey(_window, GLFW_KEY_O) == GLFW_PRESS)
	{
		yOffset += 0.25f;
	}
	cameraRef->ZoomCamera(xOffset, yOffset);
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
	}

	cameraRef->CameraLoop();
	//Each Objects Loop function

    	// Input
    	AcceptInput();
	
	//Had to Create my Own Callback to check cursor and scroll positions
	mouse_callback();
	zoom_callback();
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
//Getting input from the user, this is how we can interact with the screen
void Graphics::AcceptInput()
{
	
    // --- Follow this format anytime a key action needs to be recorded --- //
    if(glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, true);

    // Deal with Camera Settings such as Zoom and Camera Position
    if(glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS){
	if(glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cameraRef->MoveUp();
	else
		cameraRef->MoveForward();
    }
	

    if(glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS){
	    if(glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		    cameraRef->MoveDown();
	    else 
		    cameraRef->MoveBackward();

    }

    if(glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS)
	cameraRef->MoveLeft();

    if(glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	cameraRef->MoveRight();
}

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
