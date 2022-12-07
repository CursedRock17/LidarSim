#include "../../include/Graphics_Headers/Graphics.h"
//Outer Libraries //
#include <filesystem>
#include <vector>

Graphics::Graphics()
{
    RenderingInit();
}

Graphics::~Graphics()
{
    RenderingEnd();
}

//Allow resizing of window on every frame
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, 800, 600);
    }


void Graphics::mouse_callback()
{
	xPos = windowWidth / 2;
	yPos = windowHeight / 2;

	lastXPos = xPos;
	lastYPos = yPos;

	glfwGetCursorPos(window, &xPos, &yPos);

	if(lastXPos != xPos || lastYPos != yPos)
		if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			cameraRef->RotateCamera(static_cast<float>(xPos), static_cast<float>(yPos));
}

void Graphics::zoom_callback()
{		
	if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	{
		yOffset -= 0.25f;
	}

	if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		yOffset += 0.25f;
	}
	cameraRef->ZoomCamera(xOffset, yOffset);
}

void Graphics::RenderingInit()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    //Create the window with all the preattached settings
    window = glfwCreateWindow(windowWidth, windowHeight, "LidarSim" , nullptr, nullptr);
    if(!window)
    {
        std::cout << "Failed to Create a Window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, &framebuffer_size_callback);

    //Need to initalize all glad features before opengl features
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Couldn't Init Glad" << std::endl;
    }
}

void Graphics::SimulationSetup()
{
	std::vector<unsigned int> indices = {
        	0, 1, 3, //First Triangle in this case
        	1, 2, 3  //Second Triangle
    	};

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


	glEnable(GL_DEPTH_TEST);
	const char* imgLoc = "./resources/crate.png";
	const char* imgSpecularMap = "./resources/crateSpecular.png";

	std::shared_ptr<Gizmos> cube = std::make_shared<Gizmos>();
	std::shared_ptr<Gizmos> light = std::make_shared<Gizmos>();

	//Setting up Each object with the variables it would need
	// This set up currently involves creating a Gizmos Object in the code then adding it to the vector so that all objects will be revealed
	// In order to combat this we may need to add a coroutine where we're in creation mode so that we can toggle the loop
	// Code for creating a cube //
	cube->CreateShaders("./resources/shaders/vertex.vs", "./resources/shaders/fragment.fs");
	cube->CreateTextures(11, indices, vertices);
	cube->RenderTextures(imgLoc, imgSpecularMap);
	cube->objectName = "Cube";
	cube->ID = 0;
	cube->SetColor(1.0f, 0.31f, 0.51f);
	cube->SetLightPosition(1.0f, 0.0f, 0.0f);
	
	light->CreateShaders("./resources/shaders/vertexLight.vs", "./resources/shaders/lightFrag.fs");
	light->CreateTextures(11, indices, vertices);
	//Can pass nullptr if you don't have textures to apply
	light->RenderTextures(nullptr, nullptr);
	light->objectName = "Light";
	light->ID = 1;
	light->SetColor(1.0f);
	light->SetScale(0.2f);
	light->SetTranslation(1.0f, 0.0f, 0.0f);

	//Add each Gizmos Object to the vector
	gizmosVec.emplace_back(cube);
	gizmosVec.emplace_back(light);

	//Call Initialization of each Object
	for(auto &gizmos : gizmosVec)
	{
		gizmos->GizmosInit();
	}
		
	//Setting up the Camera
	cameraRef->createView(windowWidth, windowHeight, 45.0f);
}

void Graphics::SimulationLoop()
{
    //Create the infinite Loop that will run the window
    while(!glfwWindowShouldClose(window))
    {
    // Input
    AcceptInput(window);
    
    //Rendering Actions
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Change the color of screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	//Each Objects Loop function
	for(auto &gizmosRef : gizmosVec)
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
        
	// Check Buffers of Data
        glfwSwapBuffers(window);
        glfwPollEvents();

	//Had to Create my Own Callback to check cursor and scroll positions
	mouse_callback();
	zoom_callback();
    }
}

void Graphics::RenderingEnd()
{
    glfwTerminate();
}

/* Additional OpenGL funcitons */
//Getting input from the user, this is how we can interact with the screen
void Graphics::AcceptInput(GLFWwindow* window)
{
	
    // --- Follow this format anytime a key action needs to be recorded --- //
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Deal with Camera Settings such as Zoom and Camera Position
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
	if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cameraRef->MoveUp();
	else
		cameraRef->MoveForward();
    }
	

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
	    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		    cameraRef->MoveDown();
	    else 
		    cameraRef->MoveBackward();

    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	cameraRef->MoveLeft();

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	cameraRef->MoveRight();
}

/* Additional OpenGL funcitons */
