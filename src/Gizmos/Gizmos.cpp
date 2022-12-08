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

void Gizmos::GizmosInit()
{
	//Initialize the Position, Rotation, and Scale of Object
	model = glm::translate(model, Translation);
	model = glm::rotate(model, 0.0f, Rotation);
	model = glm::scale(model, Scale);

	//For the spinning use (float)glfwGetTime();
        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	//After Initing the Object in 3D Space handle Color
    	glUniform3fv(glGetUniformLocation(shaderProgram, "lightShader"), 1, &lightShader[0]);
	glUniform3fv(glGetUniformLocation(shaderProgram, "lightPos"), 1, &lightPosition[0]);
	glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 1, &viewPosition[0]);
	
	//Setup Gizmo's Material Makeup 
	glUniform3fv(glGetUniformLocation(shaderProgram, "ambientStrength"), 1, &ambientStrength[0]);
	glUniform3fv(glGetUniformLocation(shaderProgram, "specularStrength"), 1, &specularStrength[0]);
	glUniform3fv(glGetUniformLocation(shaderProgram, "diffuseStrength"), 1, &diffuseStrength[0]);
	glUniform1f(glGetUniformLocation(shaderProgram, "shiny"), specularShiny);
}

void Gizmos::GizmosLoop(glm::mat4 viewMatrix, float& screenAspect, float &FOV, bool hasTexture)
{
        //The program object that will be used for enacting the program and starting to use the VAO, then drawing it
	glUseProgram(shaderProgram);

	//After Initing the Object in 3D Space handle Color
    	glUniform3fv(glGetUniformLocation(shaderProgram, "lightShader"), 1, &lightShader[0]);
	glUniform3fv(glGetUniformLocation(shaderProgram, "lightPos"), 1, &lightPosition[0]);
	glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 1, &viewPosition[0]);
	// Orientation of Gizmo
	
	if(hasTexture){
		TexturesLoop();
	}

	//Have to use the &[0][0] for all Matrices
	unsigned int viewLocation = glGetUniformLocation(shaderProgram ,"viewer");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	
	glm::mat4 perspective = glm::perspective(glm::radians(FOV), screenAspect, 0.1f, 100.0f);
	unsigned int perspectLocation = glGetUniformLocation(shaderProgram ,"perspective");
	glUniformMatrix4fv(perspectLocation, 1, GL_FALSE, &perspective[0][0]);

	// Orientation of Gizmo

	/* Enable BasicMove in the loop when the features need to change every Frame */
	//BasicMove();
}

void Gizmos::TexturesLoop()
{
	ambientStrength = glm::vec3(0.2f);
	specularStrength = glm::vec3(1.0f);
	diffuseStrength = glm::vec3(0.5f);
	specularShiny = 64.0f;
	
	//Setup Gizmo's Material Makeup 
	glUniform3fv(glGetUniformLocation(shaderProgram, "ambientStrength"), 1, &ambientStrength[0]);
	glUniform3fv(glGetUniformLocation(shaderProgram, "specularStrength"), 1, &specularStrength[0]);
	glUniform3fv(glGetUniformLocation(shaderProgram, "diffuseStrength"), 1, &diffuseStrength[0]);
	glUniform1f(glGetUniformLocation(shaderProgram, "shiny"), specularShiny);

	// ** Must Render the Textures Before the Actual Object ** //
        glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, imgMap);
    	
        glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, imgSpecularMap);

}


// Essential Setter Functions //
glm::vec3 Gizmos::SetRotation(float xRotation, float yRotation, float zRotation)
{
	Rotation = glm::vec3(xRotation, yRotation, zRotation);
	return Rotation;
}

glm::vec3 Gizmos::SetTranslation(float xTranslation, float yTranslation, float zTranslation)
{
	Translation = glm::vec3(xTranslation, yTranslation, zTranslation);
	return Translation;
}

glm::vec3 Gizmos::SetScale(float xScale, float yScale, float zScale)
{
	Scale = glm::vec3(xScale, yScale, zScale);
	return Scale;
}

glm::vec3 Gizmos::SetColor(float red, float green, float blue)
{
	objectColor = glm::vec3(red, green, blue);
	return objectColor;
}

glm::vec3 Gizmos::SetLightPosition(float xCoord, float yCoord, float zCoord)
{
	lightPosition = glm::vec3(xCoord, yCoord, zCoord);
	return lightPosition;
}

glm::vec3 Gizmos::SetViewPos(float xCoord, float yCoord, float zCoord)
{
	viewPosition = glm::vec3(xCoord, yCoord, zCoord);
	return viewPosition;
}

// Essential Setter Functions //

//Override setFunction for equivelency across all axis
glm::vec3 Gizmos::SetRotation(float totalRotation)
{
	Rotation = glm::vec3(totalRotation);	
	return Rotation;
}

glm::vec3 Gizmos::SetTranslation(float totalTranslation)
{
	Translation = glm::vec3(totalTranslation);
	return Translation;
}

glm::vec3 Gizmos::SetScale(float totalScale)
{
	Scale = glm::vec3(totalScale);
	return Scale;
}

glm::vec3 Gizmos::SetColor(float totalColor)
{
	objectColor = glm::vec3(totalColor);
	return objectColor;
}

glm::vec3 Gizmos::SetLightPosition(float totalPosition)
{
	lightPosition = glm::vec3(totalPosition);
	return lightPosition;
}

glm::vec3 Gizmos::SetViewPos(float totalPosition)
{
	viewPosition = glm::vec3(totalPosition);
	return viewPosition;
}

glm::vec3 Gizmos::SetViewPos(glm::vec3 vectorPosition)
{
	viewPosition = vectorPosition;
	return viewPosition;
}

void Gizmos::RenderContainer()
{
	//Finish rendering the entire shape
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, totalVerticeArgs);
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void Gizmos::CreateShaders(const char* vertexPath, const char* fragmentPath) 
{
    //Going to immediatily load in our shading files
    vertexFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
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

    } catch (std::ifstream::failure& e){
        std::cout << e.what() << std::endl;
    }

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

    //- - - - - - End of Shader Code - - - - - -//
}

void Gizmos::CreateTextures(int totPoints, std::vector<unsigned int> indies, std::vector<float> verts) {	
    //Initialize Variables needed for this gizmo
    totalVerticeShaderArgs = totPoints;
    totalVerticeArgs = verts.size() / totPoints;

    //Creating the Vertex Array Object then Vertex Buffer Object, then the Element Buffer Object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    float vertices[verts.size()];
    for(int i = 0; i < verts.size(); i++)
    {
	    vertices[i] = verts.at(i);
    }

    //Copy all the data from the VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Create all the bindings for the EBO similar to VBO
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indies.data()), indies.data(), GL_STATIC_DRAW);

    //Set up the triangle
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, totalVerticeShaderArgs * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Set up the color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, totalVerticeShaderArgs * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Set up the textures
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, totalVerticeShaderArgs * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //Set Up the Lighting
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, totalVerticeShaderArgs * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}


void Gizmos::GizmosCleanUp()
{
    //When finished with the program we can delete everything
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
}


void Gizmos::RenderTextures(const char* imgLocation, const char* imgSpecularLocation)
{
	
    // Created a lamdba function that will need to be called for each image path needed
    auto bindImage = [this](const char* path) -> unsigned int
    {

	unsigned int tempTexture;
	glGenTextures(1, &tempTexture);
    
    	//Doing Loading from images, may have to be processed for more modularity
    	int imgW, imgH, numImgColChannels;
    	unsigned char *imgData = stbi_load(path, &imgW, &imgH, &numImgColChannels, 0);

    	//Generate the image as a form of respect to perspective
	//glTexImage has a texture target, the level of mipmap, the colors needed in respect to its size as well as what to make as a texture
    	if(imgData)
	{
		//Check for the way image was made
		GLenum format;
		if(numImgColChannels == 1)
			format = GL_RED;

		if(numImgColChannels == 3)
			format = GL_RGB;
		
		if(numImgColChannels == 4)
			format = GL_RGBA;
	    	
		glBindTexture(GL_TEXTURE_2D, tempTexture);
    		glTexImage2D(GL_TEXTURE_2D, 0, format, imgW, imgH, 0, format, GL_UNSIGNED_BYTE, imgData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //X coords
    		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //Y coords
    		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
   		stbi_image_free(imgData);
    	}
    	else
    	{
		if(path)
	    		std::cout << "Failed to Load Texture" << std::endl;	
    	}
	
	return tempTexture;

    }; //End of bindImage
    	
    //Find the textures for each image created
    imgMap = bindImage(imgLocation);
    imgSpecularMap = bindImage(imgSpecularLocation);

    //Link these textures in the glsl files
    glUseProgram(shaderProgram);
    //Set up Maps
    glUniform1i(glGetUniformLocation(shaderProgram, "material.diffuseMap" ), 0); 
    glUniform1i(glGetUniformLocation(shaderProgram, "material.specularMap" ), 1); 
}



void Gizmos::BasicMove()
{
	//Initialize the Position, Rotation, and Scale of Object
	model = glm::translate(model, Translation);
	model = glm::rotate(model, 0.0f, Rotation);
	model = glm::scale(model, Scale);

	//For the spinning use (float)glfwGetTime();
        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	
}
