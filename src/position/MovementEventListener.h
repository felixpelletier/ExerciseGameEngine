#pragma once

#include "MovementEvent.h"

class MovementEventListener{

	public:
		virtual void receiveMovementEvent(MovementEvent event) = 0;

};
