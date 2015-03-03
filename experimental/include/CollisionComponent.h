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
		BoundingBox getBoundingBox(){return boundingBox;};

};

}
