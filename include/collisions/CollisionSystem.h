#pragma once

#include <map>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "entities/Entity.h"
#include "Handle.h"
#include "collisions/CollisionComponent.h"
#include "collisions/CollisionEvent.h"
#include "collisions/CollisionEventListener.h"
#include "position/MovementEventListener.h"
#include "position/MovementEvent.h"
#include "System.h"

namespace Soul{

	class CollisionSystem : public System, public MovementEventListener{

		std::map<int, CollisionComponent> components;
		std::vector<CollisionEventListener*> listeners;
		void fireEvent(CollisionEvent event);
		
		void processMovementEvent(CollisionComponent* component, MovementEvent event);
		std::vector<MovementEvent> movementEvents;
	
		public:
			CollisionSystem();
			virtual void update (float dt);
			void addListener(CollisionEventListener* listener);
			Handle addComponent(CollisionComponent component);
			CollisionComponent* getComponent(Handle id);
			void receiveMovementEvent(MovementEvent event);


	};

}
