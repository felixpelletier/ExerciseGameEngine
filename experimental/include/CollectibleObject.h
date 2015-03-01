#pragma once

#include "Entity.h"

namespace Soul{

class CollectibleObject : public Entity{

	private: 
		int points = 100;
		bool collidable = true;
	public:
		CollectibleObject(GraphicsComponent graphics, CollisionComponent collisions);
		virtual void collision(Entity* other);
		virtual bool isCollidable() {return collidable;};
		int getPoints(){ return points; };

};

}
