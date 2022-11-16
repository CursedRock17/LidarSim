#include "../../include/Graphics_Headers/Graphics.h"
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

    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
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
        //Drawing shapes 

        //The program object that will be used for enacting the program and starting to use the VAO, then drawing it
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Check Buffers of Data
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Graphics::RenderingEnd()
{
    //When finished with the program we can delete everything
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    
    glfwTerminate();
}

// Entering Shaders and Fragment Vertices
void Graphics::CreateShaders()
{
    //These are the corners(vertices) of a triangle
    float vertices[] = {
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f,  -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f  // top left
    }; 

    //Use this to represent the order to draw for the EBO
    unsigned int indices[] = {
        0, 1, 3, //First Triangle in this case
        1, 2, 3  //Second Triangle
    };

    //Offshore code being used inside this file
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
        
    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";



    //Compile the vertex shader through glsl
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    
    //Checking errors in this shader
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "Vertex Shader failed to compile: " << infoLog << '\n';
    }

    //Creating the fragment shader for these shapes
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "Frag Shader failed to compile: " << infoLog << '\n';
    }

    //Creating and Linking a Shader program by adding all of the shading pieces
    shaderProgram = glCreateProgram();

    //Linking Shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    }

    //Cleanup after the project is used
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    //Creating the Vertex Array Object then Vertex Buffer Object, then the Element Buffer Object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Copy all the data from the VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Create all the bindings for the EBO similar to VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    //Set up the triangle
    glVertexAttribPointer(0, verticesAmount, GL_FLOAT, GL_FALSE, verticesAmount * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
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
