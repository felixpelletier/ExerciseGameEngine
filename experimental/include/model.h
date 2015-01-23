#pragma once
#include <misc.h>
#include <iostream>

namespace Soul{

struct Model{
	std::vector<Mesh> meshes;
	std::vector<Texture> textures;
	std::vector<tinyobj::shape_t> shapes;
};

class ModelInstance{
	public:
		int model;
		glm::mat4 modelMat;

		ModelInstance() {};
		ModelInstance(int model){ this->model = model; };
};

}
