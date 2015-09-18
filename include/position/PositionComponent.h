#pragma once

#include <glm/glm.hpp>

namespace Soul{

class PositionComponent{
	private:
	public:
		PositionComponent(int id);
		int id;
		bool enabled = true;
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 getPosition() const {return position;};
		glm::vec3 getRotation() const {return rotation;};

};

}
