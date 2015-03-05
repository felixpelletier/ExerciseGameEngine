#pragma once

#include "BoundingBox.h"
#include "Model.h"

namespace Soul{

class CollisionComponent{
	private:
		BoundingBox boundingBox;
	public:
		CollisionComponent(int id, BoundingBox box);
		int id;
		bool enabled = true;
		BoundingBox getBoundingBox(){return boundingBox;};
		glm::vec3 boundingBoxTransform;

};

}
