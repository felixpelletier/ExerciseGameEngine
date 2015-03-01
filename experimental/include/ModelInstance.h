#pragma once

#include <glm/glm.hpp>

class ModelInstance{
	public:
		int model;
		glm::mat4 modelMat;

		ModelInstance() {};
		ModelInstance(int model){ this->model = model; };
};
