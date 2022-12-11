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

	if(lastXPos != xPos || lastYPos != yPos){
		if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
			cameraRef->RotateCamera(static_cast<float>(xPos), static_cast<float>(yPos));
		} else {
			cameraRef->firstClick = true;
		}
	}
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

	//CreateCube();
	CreatePyramid();

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


	for(int i = 0; i < 5; i++){
	std::shared_ptr<Gizmos> temp = std::make_shared<Gizmos>();
	temp->CreateShaders("./resources/shaders/vertex.vs", "./resources/shaders/fragment.fs");
	temp->CreateTextures(11, vertices);
	temp->RenderTextures(imgLoc, imgSpecularMap);
	temp->objectName = "Bobbie";
	temp->ID = i + 2;
	temp->SetTranslation(0.2f, 1.0f, 0.0f);
//	gizmosVec.emplace_back(temp);
	}



	// ***** Have to Render the Lights after all the object ********* //
	light->CreateShaders("./resources/shaders/vertexLight.vs", "./resources/shaders/lightFrag.fs");
	light->CreateTextures(11, vertices);
	//Can pass nullptr if you don't have textures to apply
	light->RenderTextures(nullptr, nullptr);
	light->objectName = "Light";
	light->ID = 1;
	light->SetColor(1.0f);
	light->SetScale(0.2f);
	light->SetTranslation(0.5f, 1.75f, -1.0f);



	//Add each Gizmos Object to the vector
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


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

		if(gizmosRef->objectName == "Bob")
			gizmosRef->SetTranslation(0.01f, 0.0f, 0.0f);
		
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

//Simple Object Creation Functions
void Graphics::CreateCube()
{
	std::shared_ptr<Gizmos> cube = std::make_shared<Gizmos>();
	cube->CreateCube();

	gizmosVec.emplace_back(cube);
}


void Graphics::CreatePyramid()
{
	//Same Logic to the Cube
	std::shared_ptr<Gizmos> pyramid = std::make_shared<Gizmos>();
	pyramid->CreatePyramid();

	gizmosVec.emplace_back(pyramid);
}

//Simple Object Creation Functions

/* Additional OpenGL funcitons */
