#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Soul { 

class BoundingBox{
	public:
		BoundingBox transform(glm::mat4 matrix);
		glm::vec3 max;
		glm::vec3 min;
};



}

