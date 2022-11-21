#include "../../include/Graphics_Headers/Graphics.h"
//Outer Libraries //
#include <filesystem>

Graphics::Graphics()
{
    RenderingInit();
}

Graphics::~Graphics()
{
    RenderingEnd();
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

    //Need to initalize all glad features before opengl features
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Couldn't Init Glad" << std::endl;
    }
    glViewport(0, 0, windowWidth, windowHeight);
}

void Graphics::RenderingLoop()
{
    //Create the infinite Loop that will run the window
    while(!glfwWindowShouldClose(window))
    {
        // Input
        AcceptInput(window);

        //Rendering Actions
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Change the color of screen
        glClear(GL_COLOR_BUFFER_BIT);
	
	//Each Objects Loop function
	gizmosObject.GizmosLoop();
	//Each Objects Loop function
	
        // Check Buffers of Data
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Graphics::RenderingEnd()
{
    glfwTerminate();
}

/* Additional OpenGL funcitons */
//Allow resizing of window on every frame
void Graphics::framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, windowWidth, windowHeight);
    }

//Getting input from the user, this is how we can interact with the screen
void Graphics::AcceptInput(GLFWwindow* window)
{
    // --- Follow this format anytime a key action needs to be recorded --- //
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

/* Additional OpenGL funcitons */
