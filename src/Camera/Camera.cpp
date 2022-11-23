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

}


void Camera::createView(int screenWidth, int screenHeight, float FOV, int shaderID)
{
model = *glm::mat4(1.0f);
view = *glm::mat4(1.0f);
perspective = *glm::perspective(glm::radian(POV), float*(screenWidth / screenHeight), 0.1f, 100.0f);

//Link up these camera models with the shaders, we do this with a global shaderProgram value
// -- Do this for every camera Setting -- //

modelLocation = glGetUniformLocation(shaderID ,"spaceTransform");
glUniformMatrx4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

viewLocation = glGetUniformLocation(shaderID ,"viewer");
glUniformMatrx4fv(viewerlLocation, 1, GL_FALSE, glm::value_ptr(view));

perspectLocation = glGetUniformLocation(shaderID ,"perspective");
glUniformMatrx4fv(perspectLocation, 1, GL_FALSE, glm::value_ptr(perspective));

}
