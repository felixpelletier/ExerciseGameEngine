#pragma once

#include "BoundingBox.h"
#include "Model.h"

namespace Soul{

class CollisionComponent{
	private:
		BoundingBox boundingBox;
	public:
		CollisionComponent(){};
		CollisionComponent(BoundingBox box);
		BoundingBox getBoundingBox(){return boundingBox;};

};

}
