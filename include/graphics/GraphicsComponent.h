#pragma once

#include "ModelInstance.h"
#include "ModelManager.h"
#include "Shader.h"

namespace Soul{

class GraphicsComponent{
	public:
		glm::mat4 modelMat;
		int model_id;
		int id;
		bool enabled;
		GraphicsComponent();
		GraphicsComponent(int id, int model);

		inline bool isValid() { return model_id != 0; }; 

	private:
};

}
