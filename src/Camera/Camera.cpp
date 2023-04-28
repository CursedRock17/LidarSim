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
	cameraSpeed = 7.5f * deltaTime;

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	aspect = static_cast<float>(screenWidth_) / static_cast<float>(screenHeight_);
}

void Camera::MoveForward()
{
	cameraPos += cameraSpeed * cameraFront;
}

void Camera::MoveBackward()
{
	cameraPos -= cameraSpeed * cameraFront;
}

void Camera::MoveLeft()
{
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::MoveRight()
{
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::MoveUp()
{
	cameraPos -= cameraUp * cameraSpeed;
}

void Camera::MoveDown()
{
	cameraPos += cameraUp * cameraSpeed;
}

void Camera::RotateCamera(float xPos, float yPos)
{
	if(firstClick)
	{
		lastX = xPos;
		lastY = yPos;
		firstClick = false;
	}

	float xCurrentOffset = xPos - lastX;
	float yCurrentOffset = yPos - lastY;


	lastX = xPos;
	lastY = yPos;

	xCurrentOffset *= sensitivity;
	yCurrentOffset *= sensitivity;

	yaw += xCurrentOffset;
	pitch += yCurrentOffset;

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

glm::mat4 Camera::CameraViewMatrix()
{
	return view;
}

glm::vec3 Camera::GetCameraPosition()
{
	return cameraPos;
}

void Camera::createView(int screenWidth, int screenHeight, float FOV)
{

screenWidth_ = screenWidth;
screenHeight_ = screenHeight;
FOV_ = FOV;

lastX = static_cast<float>(screenWidth_) / 2.0f;
lastY = static_cast<float>(screenHeight_) / 2.0f;

}



