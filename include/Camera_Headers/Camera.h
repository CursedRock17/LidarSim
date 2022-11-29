#ifndef CAMERA_H
#define CAMERA_H

/* OpenGL Libraries */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <vector>
class Camera 
{
public:
Camera();
~Camera();

void CameraLoop();

void createView(int screenWidth, int screenHeight, float POV, int shaderID);
void start(std::vector<float> verts);


// Camera Changes //
void MoveForward();
void MoveBackward();
void MoveLeft();
void MoveRight();

void RotateCamera(double xPos, double yPos);
void ZoomCamera(double xOffset, double yOffset);

// Camera Changes //

float cameraSpeed = 2.5f;

private:

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int screenWidth_, screenHeight_;
float FOV_;

// Camera Poisiton Values
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

//How the Camera Sees using the 5 differenet Veiw models scuulpted in orthographic
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 perspective = glm::mat4(1.0f);

unsigned int shaderID;
};

#endif
