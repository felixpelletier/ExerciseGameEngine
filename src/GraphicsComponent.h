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
		bool enabled = true;
		virtual void draw(ModelManager& modelManager, const Shader& shader);
		GraphicsComponent(int id, int model);

	private:

};

}
