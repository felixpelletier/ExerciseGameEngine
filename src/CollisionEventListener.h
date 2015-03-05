#pragma once

#include "CollisionEvent.h"

class CollisionEventListener{

	public:
		virtual void fireEvent(CollisionEvent event) = 0;

};
