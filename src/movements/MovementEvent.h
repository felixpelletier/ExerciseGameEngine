#pragma once 

#include <glm/glm.hpp>

struct MovementEvent{
	int id;
	bool absolute = false;
	glm::vec3 translation = glm::vec3();	
	float rotation = 0;
	glm::vec3 rotationAxis = glm::vec3();
};
