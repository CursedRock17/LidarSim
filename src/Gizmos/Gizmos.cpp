#include "../../include/Gizmos_Headers/Gizmos.h"

//Include the definition for image insertion **Can only go in one cpp file
#define STB_IMAGE_IMPLEMENTATION
#include "../../include/Gizmos_Headers/stb_image.h"
#include <cmath>
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

	//After Initing the Object in 3D Space, Handle Lighting
   	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "lightShader"), 1, &lightShader[0]);
	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "lightPos"), 1, &lightPosition[0]);
	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "viewPos"), 1, &viewPosition[0]);

	//Setup Gizmo's Material Makeup
	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "ambientStrength"), 1, &ambientStrength[0]);
	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "specularStrength"), 1, &specularStrength[0]);
	glUniform3fv(glGetUniformLocation(shad.shaderProgram, "diffuseStrength"), 1, &diffuseStrength[0]);
	glUniform1f(glGetUniformLocation(shad.shaderProgram, "shiny"), specularShiny);
}

void Gizmos::GizmosUILoop()
{
    //Rotation Setter
    InputFloatState rotationState;
    glm::vec3 rotation = GetRotation();
	float rotations[6] = { rotation[0], rotation[1], rotation[2], rotation[0], rotation[1], rotation[2] };
    rotationState = ElementUI->SetRotation(rotations);

    //the rotation visuals to represent the new rotation of the object
    if(rotationState.activated){
        UpdateRotation(rotationState.floats[0], rotationState.floats[1], rotationState.floats[2]);
        SetRotation(rotationState.floats[3], rotationState.floats[4], rotationState.floats[5]);
    }

    //Translation Setter
    InputFloatState translationState;
    glm::vec3 translation = GetTranslation();
    float translations[6] = { translation[0], translation[1], translation[2], translation[0], translation[1], translation[2] };
    translationState = ElementUI->SetTranslation(translations);

    //the translation visuals to represent the new location where we must update the space to get the target then showcase that target in numbers
    if(translationState.activated){
        UpdateTranslation(translationState.floats[0], translationState.floats[1], translationState.floats[2]);
        SetTranslation(translationState.floats[3], translationState.floats[4], translationState.floats[5]);
    }


    //Scale Setter
    InputFloatState scaleState;
    glm::vec3 scale = GetScale();
    float scales[6] = { scale[0], scale[1], scale[2], scale[0], scale[1], scale[2] };
    scaleState = ElementUI->SetScale(scales);

	//the scale visuals to represent the new scale of the object which must actually update the scale then just represent it as a visuals
	if(scaleState.activated) {
        UpdateScale(scaleState.floats[0], scaleState.floats[1], scaleState.floats[2]);
        SetScale(scaleState.floats[3], scaleState.floats[4], scaleState.floats[5]);
    }

}
void Gizmos::GizmosLoop(glm::mat4 viewMatrix, float& screenAspect, float &FOV)
{
    //The program object that will be used for enacting the program and starting to use the VAO, then drawing it
	glUseProgram(shad.shaderProgram);

	//After Initing the Object in 3D Space, Handle Lighting
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
	glDrawElements(GL_TRIANGLES, totalVerticeArgs, GL_UNSIGNED_INT, 0);
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

void Gizmos::SetMaterialStrengths(float asd[]) // ambient, specular, diffuse
{
	ambientStrength = glm::vec3(asd[0]);
	specularStrength = glm::vec3(asd[1]);
	diffuseStrength = glm::vec3(asd[2]);
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

void Gizmos::CreateTextures(int totPoints, std::vector<float> verts, std::vector<int> _indices) {
    //Initialize Variables needed for this gizmo
    totalVerticeShaderArgs = totPoints;
    totalVerticeArgs = _indices.size();//verts.size() / totPoints;

    //Creating the Vertex Array Object then Vertex Buffer Object, then the Element Buffer Object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Copy all the data from the VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float/*verts*/), &verts[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() *  sizeof(GLuint/*_indices*/), &_indices[0], GL_STATIC_DRAW);

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
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shad.shaderProgram);
}


void Gizmos::RenderTextures()
{
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

    //Find the textures for each image created - Some Method in Mesh
    //imgMap = bindImage(diffuseLocation);
    //imgSpecularMap = bindImage(specularLocation);

    //Link these textures in the glsl files
    glUseProgram(shad.shaderProgram);
    //Set up Maps
    glUniform1i(glGetUniformLocation(shad.shaderProgram, "material.diffuseMap" ), 0);
    glUniform1i(glGetUniformLocation(shad.shaderProgram, "material.specularMap" ), 1);
}


bool Gizmos::CreateCustomGizmo(const std::string& filePath)
{
	shad.CreateShaders("./resources/shaders/vertexLight.vs", "./resources/shaders/basicFrag.fs");
	//Load the Import with Assimp
	Assimp::Importer importer;
	int post_processing_flags = aiProcess_CalcTangentSpace |aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType;
	const aiScene* newGizmo = importer.ReadFile(filePath, post_processing_flags);

	//We can then copy over information from the whole import
	std::vector<float> gizmoVertices;
	std::vector<int> gizmoIndices;

	//Destructure the import and insert the values into a regular Gizmo buffer
	//Look at the faces which are sets of triangles needed to make the object
	if(newGizmo){
		std::cout << "Verts: " << newGizmo->mMeshes[0]->mNumVertices << "  Faces: "<< newGizmo->mMeshes[0]->mNumFaces << " Indices: " << newGizmo->mMeshes[0]->mFaces->mNumIndices << " Meshes: " << newGizmo->mNumMeshes << std::endl;

		for(int i = 0; i < newGizmo->mNumMeshes; i++){
			for(int j = 0; j < newGizmo->mMeshes[i]->mNumFaces; j++){
				//Add all the indices
				for(int k = 0; k < newGizmo->mMeshes[i]->mFaces[j].mNumIndices; k++){ //Simple Loop to insert all the gimzo's indices
					gizmoIndices.push_back(newGizmo->mMeshes[i]->mFaces[j].mIndices[k]);
				}
				//Add all the vertices
				for(int n = 0; n < newGizmo->mMeshes[i]->mNumVertices; n++){
					//Just Transfer all the vector3Ds to floats
					for(int b = 0; b < 3; b++){
					gizmoVertices.push_back(newGizmo->mMeshes[i]->mVertices[n][b]);
				}
			    }
			}

			//At the end of each mesh we need to reset all the buffers to keep data cosnsitent
			CreateTextures(3, gizmoVertices, gizmoIndices);
			gizmoIndices.clear();
			gizmoVertices.clear();
			GizmosInit();
		}

		//CreateTextures(3, gizmoVertices, gizmoIndices);
		SetLightPosition(0.0f, 1.0f, 0.0f);
		//GizmosInit();

		return true;
	} else {
		std::cout << "Failed to Initialize Import" << std::endl;
		return false;
	}

	return false;

}

// Now the Handling of BasicGizmo Class
BasicGizmo::BasicGizmo()
{

};

BasicGizmo::~BasicGizmo()
{

};

glm::vec3 BasicGizmo::SetColor(float rgb[])
{
	objectColor = glm::vec3(rgb[0], rgb[1], rgb[2]);
	return objectColor;
}

glm::vec3 BasicGizmo::SetColor(float totalColor)
{
	objectColor = glm::vec3(totalColor);
	return objectColor;
}

glm::vec3 BasicGizmo::GetColor()
{
	return objectColor;
}

// Simple Example Functions
void BasicGizmo::CreateCube()
{

	std::vector<float> cubeVertices = {
        //Location            Textures        Normals
    -0.5f, -1.0f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
     0.5f, -1.0f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
     0.5f,  0.0f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
    -0.5f,  0.0f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,

    -0.5f, -1.0f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -1.0f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.0f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.0f,  0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f
	};

	std::vector<int> cubeIndices = {
		0, 1, 2,
		2, 3, 0, //Back Face

		4, 5, 6,
		6, 7, 4, //Front Face

		7, 3, 0,
		0, 4, 7, //Left Face

		6, 2, 1,
		1, 5, 6, //Right Face

		0, 1, 5,
		5, 4, 0, //Top Face

		3, 2, 6,
		6, 7, 3 //Bottom Face
	};

	// Code for creating a cube // - Create a Cube Gizmo then emplace it to the vector at the end

	// Just a Basic Cube Doesn't Need Extra Shaders Right Now
	shad.CreateShaders("./resources/shaders/vertex.vs", "./resources/shaders/fragment.fs");
	CreateTextures(8, cubeVertices, cubeIndices);
	objectName = "Cube";
	SetLightPosition(0.0f, 1.0f, 0.0f);
	GizmosInit();
}

void BasicGizmo::CreatePyramid()
{
	std::vector<float> pyramidVertices = {
        //Location          Textures        Normals
     -0.5f,  0.0f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
      0.5f,  0.0f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
      0.5f,  0.0f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f, //Bottom Square
     -0.5f,  0.0f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
      0.0f, -1.0f,  0.0f,  0.5f, 1.0f,  0.0f, -1.0f,  0.0f, //Front
	};

	std::vector<int> pyramidIndices = {
		0, 1, 2,
		2, 3, 0, // Bottom

		2, 4, 3, // Front
		0, 4, 1, // Back
		0, 4, 3, // Left
		1, 4, 2, // Right
	};

	shad.CreateShaders("./resources/shaders/vertex.vs", "./resources/shaders/fragment.fs");

	CreateTextures(8, pyramidVertices, pyramidIndices);
	objectName = "Pyramid";
	SetLightPosition(0.0f, 1.0f, 0.0f);
	GizmosInit();
}

void BasicGizmo::CreateLight()
{
	std::vector<float> lightVertices = {
        //Location            Textures        Normals
    -0.5f, -1.0f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
     0.5f, -1.0f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
     0.5f,  0.0f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
    -0.5f,  0.0f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,

    -0.5f, -1.0f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -1.0f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.0f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.0f,  0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f
	};

	std::vector<int> lightIndices = {
		0, 1, 2,
		2, 3, 0, //Back Face

		4, 5, 6,
		6, 7, 4, //Front Face

		7, 3, 0,
		0, 4, 7, //Left Face

		6, 2, 1,
		1, 5, 6, //Right Face

		0, 1, 5,
		5, 4, 0, //Top Face

		3, 2, 6	,
		6, 7, 3 //Bottom Face
	};


	// ***** Have to Render the Lights after all the object ********* //
	shad.CreateShaders("./resources/shaders/vertexLight.vs", "./resources/shaders/lightFrag.fs");
	CreateTextures(8, lightVertices, lightIndices);
	//Can pass nullptr if you don't have textures to apply
	objectName = "Light";
	SetScale(0.2f);
	SetTranslation(1.0f, 1.0f, -1.0f);
	GizmosInit();
}

// Simple Example Functions

void BasicGizmo::CreateFloor()
{
	std::vector<float> floorVertices = {
        //Location
    -10.0f,  0.0f, -10.0f,
     10.0f,  0.0f, -10.0f,
     10.0f, 0.15, -10.0f,
    -10.0f, 0.15, -10.0f,

    -10.0f,  0.0f,  10.0f,
     10.0f,  0.0f,  10.0f,
     10.0f, 0.15,  10.0f,
    -10.0f, 0.15,  10.0f
};

	std::vector<int> floorIndices = {
		0, 1, 2,
		2, 3, 0, //Back Face

		4, 5, 6,
		6, 7, 4, //Front Face

		7, 3, 0,
		0, 4, 7, //Left Face

		6, 2, 1,
		1, 5, 6, //Right Face

		0, 1, 5,
		5, 4, 0, //Top Face

		3, 2, 6,
		6, 7, 3 //Bottom Face
	};

	// Code for creating a cube // - Create a Cube Gizmo then emplace it to the vector at the end

	// Just a Basic Cube Doesn't Need Extra Shaders Right Now
	shad.CreateShaders("./resources/shaders/vertexLight.vs", "./resources/shaders/basicFrag.fs");
	CreateTextures(3, floorVertices, floorIndices);
	objectName = "Floor";
	SetLightPosition(0.0f, 1.0f, 0.0f);
	GizmosInit();
}

void BasicGizmo::GizmosInit()
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

void BasicGizmo::GizmosLoop(glm::mat4 viewMatrix, float& screenAspect, float &FOV)
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

void BasicGizmo::GizmosUILoop()
{
    // Color Setter
    float color[3] = { GetColor()[0], GetColor()[1], GetColor()[2] };
    SetColor(ElementUI->SetColor(color));


    //Rotation Setter
    InputFloatState rotationState;
    glm::vec3 rotation = GetRotation();
	float rotations[6] = { rotation[0], rotation[1], rotation[2], rotation[0], rotation[1], rotation[2] };
    rotationState = ElementUI->SetRotation(rotations);

    //the rotation visuals to represent the new rotation of the object
    if(rotationState.activated){
        UpdateRotation(rotationState.floats[0], rotationState.floats[1], rotationState.floats[2]);
        SetRotation(rotationState.floats[3], rotationState.floats[4], rotationState.floats[5]);
    }

    //Translation Setter
    InputFloatState translationState;
    glm::vec3 translation = GetTranslation();
    float translations[6] = { translation[0], translation[1], translation[2], translation[0], translation[1], translation[2] };
    translationState = ElementUI->SetTranslation(translations);

    //the translation visuals to represent the new location where we must update the space to get the target then showcase that target in numbers
    if(translationState.activated){
        UpdateTranslation(translationState.floats[0], translationState.floats[1], translationState.floats[2]);
        SetTranslation(translationState.floats[3], translationState.floats[4], translationState.floats[5]);
    }


    //Scale Setter
    InputFloatState scaleState;
    glm::vec3 scale = GetScale();
    float scales[6] = { scale[0], scale[1], scale[2], scale[0], scale[1], scale[2] };
    scaleState = ElementUI->SetScale(scales);

	//the scale visuals to represent the new scale of the object which must actually update the scale then just represent it as a visuals
	if(scaleState.activated) {
        UpdateScale(scaleState.floats[0], scaleState.floats[1], scaleState.floats[2]);
        SetScale(scaleState.floats[3], scaleState.floats[4], scaleState.floats[5]);
    }

    ElementUI->ElementFolder.SetupWindow("ElementFolder");

    //Setup the diffuse and secular texture maps
    ElementUI->CreateFolder("Diffuse map");

    ImGui::SameLine();
		if(ImGui::Button("Set diffuse")){
			diffuseLocation = ElementUI->ElementFolder.GetTargetPath();
			RenderTextures();
    		SetColor(0.0f);
		}

    ElementUI->CreateFolder("Specular map");

    ImGui::SameLine();
		if(ImGui::Button("Set specular")){
			diffuseLocation = ElementUI->ElementFolder.GetTargetPath();
			RenderTextures();
    		SetColor(0.0f);
		}

    glm::vec3 strength  = GetMaterialStrengths();
    float strengths[3] = { strength[0], strength[1], strength[2] };
    SetMaterialStrengths(ElementUI->SetStrengths(strengths));

    float shiny = GetMaterialShine();
    SetMaterialShine(ElementUI->SetShiny(shiny));


}

void BasicGizmo::RenderTextures()
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
