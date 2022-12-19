#include "../../include/Application_Headers/Application.h"

Application::Application()
{
	ApplicationLoad();
}

Application::~Application()
{
	ApplicationClose();
}

//Allow resizing of window on every frame
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    { 
        glViewport(0, 0, width, height);
    }

// Basic Constructor and Deconstructor Actions of the application
void Application::ApplicationLoad()
{
    //Setup the window and all the necessary settings
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

    // SETUP OTHER OBJECTS
    // Must give each object access to the window and all of the gizmos that will be applied within each scene
	GraphicsRef = std::make_shared<Graphics>(window, windowWidth, windowHeight, ApplicationGizmos);
	UiRef = std::make_shared<UI>(window, windowHeight, windowWidth, ApplicationGizmos); 

	GraphicsRef->SimulationSetup();
	UiRef->SetupMenu();	

    // SETUP OTHER OBJECTS

}

void Application::ApplicationClose()
{
    //Deletes all the stuff the app had to create
    glfwTerminate();
}

void Application::ApplicationLoop()
{
//Create the infinite Loop that will run the window

// In this loop rendering order is extremely important going to need to add Layers in application

while(!glfwWindowShouldClose(window))
{
	//Rendering Actions
	glfwPollEvents();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Change the color of screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//At the start of each iteration of the loop we need to make sure the Application's Gizmos are at their maximum update and each object updates 
	//To have their Gizmos at max update, because we used vectors which have allocators, we can't pass them as pointers so we have to update
	//Application Gizmos with the only thing that can change them
	
	ApplicationGizmos = GraphicsRef->GetApplicationGizmos();

	GraphicsRef->SetApplicationGizmos(ApplicationGizmos);
	UiRef->SetApplicationGizmos(ApplicationGizmos);

    //Each Objects Loop function
    

    //Update the Menu Layer
    GraphicsRef->SimulationLoop();
    UiRef->MenuLoop();

	std::cout << ApplicationGizmos.size() << std::endl;

    // Check Buffers of Data
    glfwSwapBuffers(window);

    // Input
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	glfwSetWindowShouldClose(window, true);

} // End of While Loop

}
