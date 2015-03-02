#include <Entity.h>

namespace Soul { 


Entity::Entity(Handle graphics, CollisionComponent collisions){

	this->graphics = graphics;
	this->collisions = collisions;
}

void Entity::collision(Entity* other){

}

}




