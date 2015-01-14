#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Soul { 

class BoundingBox{
	public:
		BoundingBox transform(glm::mat4 matrix);
		bool intersect(BoundingBox other);
		glm::vec3 max;
		glm::vec3 min;
};



}

