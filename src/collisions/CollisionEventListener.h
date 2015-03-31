#pragma once

#include "CollisionEvent.h"

class CollisionEventListener{

	public:
		virtual void receiveCollisionEvent(CollisionEvent event) = 0;

};
