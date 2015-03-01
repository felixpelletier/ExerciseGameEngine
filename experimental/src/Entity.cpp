#include <Entity.h>

namespace Soul { 


Entity::Entity(GraphicsComponent graphics, CollisionComponent collisions){

	this->graphics = graphics;
	this->collisions = collisions;
}

void Entity::collision(Entity* other){

}

}




