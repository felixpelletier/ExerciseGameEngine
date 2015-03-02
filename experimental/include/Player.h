#pragma once

#include "Entity.h"
#include "GraphicsComponent.h"
#include "CollisionComponent.h"

namespace Soul{

class Player : public Entity{

	private: 
		bool collidable = true;
		int points = 0;

	public:
		Player(Handle graphics, CollisionComponent collisions);
		virtual void collision(Entity* other);
		virtual bool isCollidable() {return collidable;};
		int getPoints(){ return points; };

};

}
