#pragma once

#include "ModelInstance.h"

namespace Soul{

class GraphicsComponent{
	public:
		glm::mat4 modelMat;
		int model_id;
		int id;
		bool enabled = true;
		GraphicsComponent(int id, int model);

};

}
