#include "../../include/Gizmos_Headers/Gizmos.h"

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
	glUseProgram(shad.shaderProgram);
	
	//Initialize the Position, Rotation, and Scale of Object
	model = glm::translate(model, Translation);
	model = glm::scale(model, Scale);

	//Control Rotation based on the 3 Right Axis Local Vectors
	model = glm::rotate(model, glm::radians(Rotation[0]) , glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation[1]) , glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation[2]) , glm::vec3(0.0f, 0.0f, 1.0f));

	//For the spinning use (float)glfwGetTime();
    modelLoc = glGetUniformLocation(shad.shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	//After Initing the Object in 3D Space handle Color
   	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "objectColor"), 1, &objectColor[0]);
   	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "lightShader"), 1, &lightShader[0]);
	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "lightPos"), 1, &lightPosition[0]);
	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "viewPos"), 1, &viewPosition[0]);
	
	//Setup Gizmo's Material Makeup 
	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "ambientStrength"), 1, &ambientStrength[0]);
	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "specularStrength"), 1, &specularStrength[0]);
	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "diffuseStrength"), 1, &diffuseStrength[0]);
	glUniform1f(glGetUniformLocation(shad.shaderProgram, "shiny"), specularShiny);
}

void Gizmos::GizmosLoop(glm::mat4 viewMatrix, float& screenAspect, float &FOV)
{
    //The program object that will be used for enacting the program and starting to use the VAO, then drawing it
	glUseProgram(shad.shaderProgram);

	//After Initing the Object in 3D Space handle Color
   	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "objectColor"), 1, &objectColor[0]);
   	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "lightShader"), 1, &lightShader[0]);
	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "lightPos"), 1, &lightPosition[0]);
	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "viewPos"), 1, &viewPosition[0]);
	
	//We have to make sure each object has a defaulted texture, then we can see if(hasTexture) to see what we need to apply
    glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
	
	if(hasTexture){
		TexturesLoop();
	}
	
	//Have to use the &[0][0] for all Matrices
	unsigned int viewLocation = glGetUniformLocation(shad.shaderProgram ,"viewer");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix[0][0]);
	
	glm::mat4 perspective = glm::perspective(glm::radians(FOV), screenAspect, 0.1f, 100.0f);
	unsigned int perspectLocation = glGetUniformLocation(shad.shaderProgram ,"perspective");
	glUniformMatrix4fv(perspectLocation, 1, GL_FALSE, &perspective[0][0]);

	// Orientation of Gizmo
}

void Gizmos::TexturesLoop()
{
	//Setup Gizmo's Material Makeup 
	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "ambientStrength"), 1, &ambientStrength[0]);
	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "specularStrength"), 1, &specularStrength[0]);
	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "diffuseStrength"), 1, &diffuseStrength[0]);
	glUniform1f(glGetUniformLocation(shad.shaderProgram, "shiny"), specularShiny);

	// ** Must Render the Textures Before the Actual Object ** //
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, imgMap);
    
    glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, imgSpecularMap);
}

void Gizmos::RenderContainer()
{
	//Finish rendering the entire shape
	glDrawArrays(GL_TRIANGLES, 0, totalVerticeArgs);
}

//This RenderContainer Represents
void Gizmos::RenderContainer(int numObjects)
{
	//Finish rendering the entire shape
	glDrawArraysInstanced(GL_TRIANGLES, 0, totalVerticeArgs, numObjects);
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

void Gizmos::SetMaterialStrengths(float ambient, float specular, float diffuse)
{
	ambientStrength = glm::vec3(ambient);
	specularStrength = glm::vec3(specular);
	diffuseStrength = glm::vec3(diffuse);
}

void Gizmos::SetMaterialShine(float materialShine)
{
	specularShiny = materialShine;
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

// * List of Updater Functions * //

glm::vec3 Gizmos::UpdateRotation(float xRotation, float yRotation, float zRotation)
{
	Rotation = glm::vec3(xRotation, yRotation, zRotation);
	model = glm::rotate(model, glm::radians(Rotation[0]) , glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation[1]) , glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation[2]) , glm::vec3(0.0f, 0.0f, 1.0f));

    modelLoc = glGetUniformLocation(shad.shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	return Rotation;
}

glm::vec3 Gizmos::UpdateTranslation(float xTranslation, float yTranslation, float zTranslation)
{
	Translation = glm::vec3(xTranslation, yTranslation, zTranslation);
	
	//Actually Move the object
	model = glm::translate(model, Translation);
    modelLoc = glGetUniformLocation(shad.shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	return Translation;
}

glm::vec3 Gizmos::UpdateScale(float xScale, float yScale, float zScale)
{
	Scale = glm::vec3(xScale, yScale, zScale);
	model = glm::scale(model, Scale);
	
        modelLoc = glGetUniformLocation(shad.shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	return Scale;
}

//Override UpdateObject for equivelency across all axis
glm::vec3 Gizmos::UpdateRotation(float totalRotation)
{
	Rotation = glm::vec3(totalRotation);	
	model = glm::rotate(model, glm::radians(Rotation[0]) , glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation[1]) , glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation[2]) , glm::vec3(0.0f, 0.0f, 1.0f));

        modelLoc = glGetUniformLocation(shad.shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	return Rotation;
}

glm::vec3 Gizmos::UpdateTranslation(float totalTranslation)
{
	Translation = glm::vec3(totalTranslation);
	
	//Actually Move the object
	model = glm::translate(model, Translation);
        modelLoc = glGetUniformLocation(shad.shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	return Translation;
}

glm::vec3 Gizmos::UpdateScale(float totalScale)
{
	Scale = glm::vec3(totalScale);
	model = glm::scale(model, Scale);
	
        modelLoc = glGetUniformLocation(shad.shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	return Scale;
}
// * List of Updater Functions * //


//List of Getter Functions
glm::vec3 Gizmos::GetRotation()
{
	return Rotation;
}

glm::vec3 Gizmos::GetTranslation()
{
	return Translation;
}

glm::vec3 Gizmos::GetScale()
{
	return Scale;
}

glm::vec3 Gizmos::GetColor()
{
	return objectColor;
}

glm::vec3 Gizmos::GetMaterialStrengths()
{
	glm::vec3 tempStrengths = glm::vec3(ambientStrength[0], specularStrength[0], diffuseStrength[0]);
	return tempStrengths;
}

float Gizmos::GetMaterialShine()
{
	return specularShiny;
}

void Gizmos::ResetGizmoSpace()
{
	//The default world space values are jsut those for the rotation, translation, and scale in the header file
	SetRotation(0.0f);
	SetTranslation(0.0f);
	SetScale(1.0f);

	UpdateGizmoSpace();	

}

void Gizmos::UpdateGizmoSpace()
{
	//Initialize the Position, Rotation, and Scale of Object
	model = glm::translate(model, Translation);
	model = glm::rotate(model, glm::radians(Rotation[0]) , glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation[1]) , glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation[2]) , glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, Scale);

	//For the spinning use (float)glfwGetTime() in the second slot of rotation;
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

//Updater Functions to Create Changes before the total loop

void Gizmos::CreateTextures(int totPoints, std::vector<float> verts) {	
    //Initialize Variables needed for this gizmo
    totalVerticeShaderArgs = totPoints;
    totalVerticeArgs = verts.size() / totPoints;

    //Creating the Vertex Array Object then Vertex Buffer Object, then the Element Buffer Object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    float vertices[verts.size()];
    for(int i = 0; i < verts.size(); i++)
    {
	    vertices[i] = verts.at(i);
    }

    //Copy all the data from the VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Set up the triangle
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, totalVerticeShaderArgs * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Set up the textures
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, totalVerticeShaderArgs * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Set Up the Lighting
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, totalVerticeShaderArgs * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}


void Gizmos::GizmosCleanUp()
{
    //When finished with the program we can delete everything
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shad.shaderProgram);
}


void Gizmos::RenderTextures()
{	
    if(diffuseLocation != "" && specularLocation != ""){
    	hasTexture = true;

    // Created a lamdba function that will need to be called for each image path needed
    auto bindImage = [this](std::filesystem::path path) -> unsigned int
    {
	unsigned int tempTexture;
	glGenTextures(1, &tempTexture);
    
    	//Doing Loading from images, may have to be processed for more modularity
    	int imgW, imgH, numImgColChannels;

	//Make Sure Image Runs Top Down
	stbi_set_flip_vertically_on_load(true);

    	unsigned char *imgData = stbi_load(path.c_str(), &imgW, &imgH, &numImgColChannels, 0);

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
		if(path != "")
	    		std::cout << "Failed to Load Texture" << std::endl;	
    	}

	//If we are working with the ImGui scene specifically, then we need to transform this object into a texture
	return tempTexture;

    }; //End of bindImage
    	
    //Find the textures for each image created
    imgMap = bindImage(diffuseLocation);
    imgSpecularMap = bindImage(specularLocation);
	
    }
    //Link these textures in the glsl files
    glUseProgram(shad.shaderProgram);
    //Set up Maps
    glUniform1i(glGetUniformLocation(shad.shaderProgram, "material.diffuseMap" ), 0); 
    glUniform1i(glGetUniformLocation(shad.shaderProgram, "material.specularMap" ), 1);
}


// Simple Example Functions

void Gizmos::CreateCube()
{
	std::vector<float> cubeVertices = {
        //Location            Textures        Normals      
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f, 
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -1.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f, 0.0f,
 
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f, 
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f
	}; 

	// Code for creating a cube // - Create a Cube Gizmo then emplace it to the vector at the end 

	// Just a Basic Cube Doesn't Need Extra Shaders Right Now
	shad.CreateShaders("./resources/shaders/vertex.vs", "./resources/shaders/fragment.fs");
	CreateTextures(8, cubeVertices);
	objectName = "Cube";
	SetLightPosition(0.0f, 1.0f, 0.0f);
	GizmosInit();
}

void Gizmos::CreatePyramid()
{
	std::vector<float> pyramidVertices = {
        //Location          Textures        Normals      
     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f, //Bottom Square
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
     0.0f,  0.5f,  0.0f,  0.5f, 1.0f,  0.0f, -1.0f,  0.0f, //Front
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
     
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
     0.0f,  0.5f,  0.0f,  0.5f, 1.0f,  0.0f, -1.0f,  0.0f, //Back
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
     0.0f,  0.5f,  0.0f,  0.5f, 1.0f,  0.0f, -1.0f,  0.0f, //Left
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,

     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
     0.0f,  0.5f,  0.0f,  0.5f, 1.0f,  0.0f, -1.0f,  0.0f, //Right
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
	};


	shad.CreateShaders("./resources/shaders/vertex.vs", "./resources/shaders/fragment.fs");
	CreateTextures(8, pyramidVertices);
	objectName = "Pyramid";
	SetLightPosition(0.0f, 1.0f, 0.0f);
	GizmosInit();
}

void Gizmos::CreateLight()
{
	std::vector<float> lightVertices = {
        //Location        Textures        Normals      
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f, 
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -1.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f, 0.0f,
 
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f, 
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f
	}; 


	// ***** Have to Render the Lights after all the object ********* //
	shad.CreateShaders("./resources/shaders/vertexLight.vs", "./resources/shaders/lightFrag.fs");
	CreateTextures(8, lightVertices);
	//Can pass nullptr if you don't have textures to apply
	objectName = "Light";
	SetScale(0.2f);
	SetTranslation(1.0f, 1.0f, -1.0f);
	GizmosInit();
}

// Simple Example Functions

