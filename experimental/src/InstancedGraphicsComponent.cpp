#include "InstancedGraphicsComponent.h"
#include "GraphicsComponent.h"
#include "ModelInstance.h"
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

namespace Soul{

InstancedGraphicsComponent::InstancedGraphicsComponent(ModelInstance model, std::vector<glm::vec3> positions)
: GraphicsComponent(model)
{
	this->positions = positions;

	glGenBuffers(1, &instPosBuf);
	glBindBuffer(GL_ARRAY_BUFFER, instPosBuf);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);
	
}

}
