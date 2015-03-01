#pragma once

#include "BoundingBox.h"
#include "Model.h"

namespace Soul{

class CollisionComponent{
	private:
		BoundingBox boundingBox;
	public:
		CollisionComponent(){};
		CollisionComponent(Model* model);
		BoundingBox getBoundingBox(){return boundingBox;};

};

}
