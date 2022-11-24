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
//Link up these camera models with the shaders, we do this with a global shaderProgram value
// -- Do this for every camera Setting -- //

unsigned int modelLocation = glGetUniformLocation(shaderID ,"spaceTransform");
glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

unsigned int viewLocation = glGetUniformLocation(shaderID ,"viewer");
glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

unsigned int perspectLocation = glGetUniformLocation(shaderID ,"perspective");
glUniformMatrix4fv(perspectLocation, 1, GL_FALSE, glm::value_ptr(perspective));

}



void Camera::createView(int screenWidth, int screenHeight, float FOV, int shaderID_)
{
float aspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);

shaderID = shaderID_;
model = glm::mat4(1.0f);
view = glm::mat4(1.0f);
perspective = glm::mat4(1.0f);

//Can now set up the camera object in comparison to objects
perspective = glm::perspective(glm::radians(FOV), aspect, 0.1f, 100.0f);
}
