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

//Have to use the &[0][0] for all Matrices
unsigned int viewLocation = glGetUniformLocation(shaderID ,"viewer");
glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

unsigned int perspectLocation = glGetUniformLocation(shaderID ,"perspective");
glUniformMatrix4fv(perspectLocation, 1, GL_FALSE, &perspective[0][0]);

}


void Camera::createView(int screenWidth, int screenHeight, float FOV, int shaderID_)
{


float aspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);

shaderID = shaderID_;

//Can now set up the camera object in comparison to objects
view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
perspective = glm::perspective(glm::radians(FOV), aspect, 0.1f, 100.0f);

//Have to use the &[0][0] for all Matrices
unsigned int viewLocation = glGetUniformLocation(shaderID ,"viewer");
glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

unsigned int perspectLocation = glGetUniformLocation(shaderID ,"perspective");
glUniformMatrix4fv(perspectLocation, 1, GL_FALSE, &perspective[0][0]);
}



