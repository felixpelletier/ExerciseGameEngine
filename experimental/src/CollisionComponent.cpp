#include "CollisionComponent.h"
#include "BoundingBox.h"

namespace Soul{

CollisionComponent::CollisionComponent(int id, BoundingBox box){

	this->id = id;
	boundingBox = box;

}

}

