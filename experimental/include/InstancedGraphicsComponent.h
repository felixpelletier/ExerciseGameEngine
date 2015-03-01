#pragma once

#include "GraphicsComponent.h"
#include "ModelInstance.h"
#include <glm/glm.hpp>
#include <vector>
#include <GL/glew.h>

namespace Soul{

class InstancedGraphicsComponent : public GraphicsComponent{
		static const GraphicComponentType type = Instanced;
	public:
		InstancedGraphicsComponent() {};
		InstancedGraphicsComponent(ModelInstance model, std::vector<glm::vec3> positions);
		std::vector<glm::vec3> positions;
		GLuint instPosBuf;
		unsigned getInstanceCount() {return positions.size();};
		virtual GraphicComponentType getType() { return type; };
};

}
