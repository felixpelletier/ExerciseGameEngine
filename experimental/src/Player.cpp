#include "Player.h"
#include "GraphicsComponent.h"
#include "CollisionComponent.h"
#include "Entity.h"
#include "CollectibleObject.h"

namespace Soul{

Player::Player(Handle graphics, CollisionComponent collisions) : Entity::Entity(graphics, collisions){}

void Player::collision(Entity* other){

	CollectibleObject* collect = (CollectibleObject*) other;
	points += collect->getPoints(); 

	std::cout << points << " points\n";

}

}
