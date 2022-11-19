#include <iostream>


#include "../../include/Space_Headers/Space.h"

Space::Space()
{
}

Space::~Space()
{
}

void Space::BasicMove()
{
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans_dir = glm::mat4(1.0f);
	trans_dir = glm::rotate(trans_dir, glm::radians(90.0f), glm::vec3(0.0, 0.0, 0.0));
	trans_dir = glm::scale(trans_dir, glm::vec3(0.5, 0.5, 0.5));
	vec = trans_dir * vec;
	std::cout << vec.x << " " << vec.y << " " << vec.z << " " << std::endl;
}
