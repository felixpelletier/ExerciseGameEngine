#pragma once

#include "config.h"
#include <cstdint>
#include <vector>
#include <map>
#include <cstring>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <tinyobjloader/tiny_obj_loader.h>
#include "misc.h"

#include "Handle.h"

namespace Soul { 

class Entity{
	public:
		Entity();
		Handle graphics;
		Handle collisions;
		int id;
	private:
		static int id_counter;
		std::vector<Handle> components;

};

}
