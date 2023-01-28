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

void createView(int screenWidth, int screenHeight, float POV);
void start(std::vector<float> verts);


// Camera Changes //
void MoveForward();
void MoveBackward();
void MoveLeft();
void MoveRight();
void MoveUp();
void MoveDown();

void RotateCamera(float xPos, float yPos);
void ZoomCamera(float xOffset, float yOffset);

glm::mat4 CameraViewMatrix();
glm::vec3 GetCameraPosition();

// Camera Changes //

float cameraSpeed{25.0f};
float FOV_{45.0f};
float aspect;
bool firstClick{true};

private:

float deltaTime{0.0f};
float lastFrame{0.0f};

int screenWidth_, screenHeight_;

//Rotation Values
const float sensitivity{0.25f};
float lastX;
float lastY;

float yaw{-90.0f};
float pitch{0.0f};

// Camera Poisiton Values
glm::vec3 cameraPos = glm::vec3(20.0f, -10.0f, 15.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 2.5f, 0.0f);

//How the Camera Sees using the 5 differenet Veiw models scuulpted in orthographic
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 perspective = glm::mat4(1.0f);

unsigned int shaderID;
};

#endif
