#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Model.h" 

namespace Soul { 

class BoundingBox{
	public:
		BoundingBox(){};
		BoundingBox(const Model* model);
		BoundingBox transform(glm::mat4 matrix);
		bool intersect(BoundingBox other);
		glm::vec3 max;
		glm::vec3 min;
};



}

