#pragma once

#include <vector>
#include "Mesh.h"
#include "Texture.h"
#include "tiny_obj_loader.h"

namespace Soul{

struct Model{
	std::vector<Mesh> meshes;
	std::vector<Texture> textures;
	std::vector<tinyobj::shape_t> shapes;
};

}
