#include <iostream>

#include "../../include/Camera_Headers/Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}


void Camera::CameraLoop()
{

	float currentFrame =  static_cast<float>(glfwGetTime());
	
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	//Have to use the &[0][0] for all Matrices
	unsigned int viewLocation = glGetUniformLocation(shaderID ,"viewer");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);


	float aspect = static_cast<float>(screenWidth_) / static_cast<float>(screenHeight_);

	//Can now set up the camera object in comparison to objects
	perspective = glm::perspective(glm::radians(FOV_), aspect, 0.1f, 100.0f);

	unsigned int perspectLocation = glGetUniformLocation(shaderID ,"perspective");
	glUniformMatrix4fv(perspectLocation, 1, GL_FALSE, &perspective[0][0]);
}

void Camera::MoveForward()
{
	cameraSpeed = 2.5f * deltaTime;
	cameraPos += cameraSpeed * cameraFront;
}

void Camera::MoveBackward()
{
	cameraSpeed = 2.5f * deltaTime;
	cameraPos -= cameraSpeed * cameraFront;
}

void Camera::MoveLeft()
{
	cameraSpeed = 2.5f * deltaTime;
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::MoveRight()
{
	cameraSpeed = 2.5f * deltaTime;
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::RotateCamera(float xPos, float yPos)
{
	float yaw = -90.0f;
	float pitch = 0.0f;
	
	float lastX = static_cast<float>(screenWidth_) / 2.0f;
	float lastY = static_cast<float>(screenHeight_) / 2.0f;

	float xCurrentOffset = xPos - lastX;
	float yCurrentOffset = yPos - lastY;
	lastX = xPos;
	lastY = yPos;

	const float sensitivity = 0.1f;
	xCurrentOffset *= sensitivity;
	yCurrentOffset *= sensitivity;

	yaw = xCurrentOffset;
	pitch = yCurrentOffset;

	if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;

	//Set up the the triangle when looking across these axis
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch)); //Yaw
	direction.y = sin(glm::radians(pitch)); //Pitch
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch)); //Roll

	cameraFront = glm::normalize(direction);

}


void Camera::ZoomCamera(float xOffset, float yOffset)
{
	FOV_ = yOffset;
	if(FOV_ < 1.0f)
		FOV_ = 1.0f;
	if(FOV_ > 45.0f)
		FOV_ = 45.0f;
}


void Camera::createView(int screenWidth, int screenHeight, float FOV, int shaderID_)
{

screenWidth_ = screenWidth;
screenHeight_ = screenHeight;
FOV_ = FOV;
shaderID = shaderID_;

//Have to use the &[0][0] for all Matrices
unsigned int viewLocation = glGetUniformLocation(shaderID ,"viewer");
glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

unsigned int perspectLocation = glGetUniformLocation(shaderID ,"perspective");
glUniformMatrix4fv(perspectLocation, 1, GL_FALSE, &perspective[0][0]);
}



