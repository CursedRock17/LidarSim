#ifndef CAMERA_H
#define CAMERA_H

/* OpenGL Libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Camera 
{
public:
Camera();
~Camera();

void CameraLoop();
private:

void createView(int screenWidth, int screenHeight, float POV, int shaderID);

glm::mat4* model{nullptr};
glm::mat4* view{nullptr);
glm::mat4* perspective{nullptr}


};

#endif
