#include "../../include/Gizmos_Headers/Gizmos.h"

#include <filesystem>

//Include the definition for image insertion **Can only go in one cpp file
#define STB_IMAGE_IMPLEMENTATION
#include "../../include/Gizmos_Headers/stb_image.h"	

Gizmos::Gizmos()
{
}

Gizmos::~Gizmos()
{
	GizmosCleanUp();
}

void Gizmos::GizmosLoop()
{
        //The program object that will be used for enacting the program and starting to use the VAO, then drawing it
        glBindTexture(GL_TEXTURE_2D, texture);
	glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void Gizmos::CreateShaders(const char* vertexPath, const char* fragmentPath)
{

    //Going to immediatily load in our shading files
    try { 
	//Copying the glsl files into cpp code
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);

        std::stringstream VertexStreamString, FragmentStreamString; 
        VertexStreamString << vertexFile.rdbuf();
        FragmentStreamString << fragmentFile.rdbuf();

        vertexFile.close();
        fragmentFile.close();

        vertexBuffer = VertexStreamString.str();
        fragmentBuffer = FragmentStreamString.str();

    } catch (std::exception& e){
        std::cout << e.what() << std::endl;
    }

    //These are the corners(vertices) of a triangle
    //Then we have the color values to pass compared to the vertices
    //After we have where the textures need to be mapped similar to how colors work, but only xy plane
    float vertices[] = {
        //Location              Colors            Textures
        0.5f,   0.5f, 0.0f,    1.0f, 0.0f, 0.0f,  1.0f, 1.0f,              // top right
        0.5f,  -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,  1.0f, 0.0f,              // bottom right
        -0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,  0.0f, 0.0f,              // bottom left
        -0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 1.0f,  0.0f, 1.0f              // top left
    }; 

    //Use this to represent the order to draw for the EBO
    unsigned int indices[] = {
        0, 1, 3, //First Triangle in this case
        1, 2, 3  //Second Triangle
    };

    const char* vertexShaderSource = vertexBuffer.c_str();
    const char* fragmentShaderSource = fragmentBuffer.c_str();

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
    glVertexAttribPointer(0, verticesAmount, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Set up color
    glVertexAttribPointer(1, verticesAmount, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Set up the textures
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Gizmos::GizmosCleanUp()
{
    //When finished with the program we can delete everything
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}


void Gizmos::RenderTextures()
{
    //Doing Loading from images, may have to be processed for more modularity
    int imgW, imgH, numImgColChannels;
    unsigned char *imgData = stbi_load("/Users/cursedrock17/Documents/Coding/CPP/LidarSim/src/Graphics/test.jpg", &imgW, &imgH, &numImgColChannels, 0);

    //Create and bind the texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); //X coords
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); //Y coords

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Generate the image as a form of respect to perspective
    //glTexImage has a texture target, the level of mipmap, the colors needed in respect to its size as well as what to make as a texture
    if(imgData){
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgW, imgH, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
    	glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
	std::cout << "Failed to Load Texture" << std::endl;	
    }

    stbi_image_free(imgData);
}


void Gizmos::BasicMove(unsigned int shaderID)
{
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans_dir = glm::mat4(1.0f);
	trans_dir = glm::rotate(trans_dir, glm::radians(90.0f), glm::vec3(0.0, 0.0, 0.0));
	trans_dir = glm::scale(trans_dir, glm::vec3(0.5, 0.5, 0.5));
	vec = trans_dir * vec;
	std::cout << vec.x << " " << vec.y << " " << vec.z << " " << std::endl;
}