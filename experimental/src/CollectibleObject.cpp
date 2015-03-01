#include "CollectibleObject.h"

namespace Soul{

CollectibleObject::CollectibleObject(GraphicsComponent graphics, CollisionComponent collisions) : Entity::Entity(graphics, collisions){}

void CollectibleObject::collision(Entity* other){

	this->visible = false;

}

}
