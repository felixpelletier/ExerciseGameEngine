#pragma once

#include <map>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Entity.h"
#include "Handle.h"
#include "CollisionComponent.h"
#include "CollisionEvent.h"
#include "CollisionEventListener.h"
#include "MovementEventListener.h"
#include "MovementEvent.h"
#include "systems/System.h"

namespace Soul{

	class CollisionSystem : public System, public MovementEventListener{

		std::map<int, CollisionComponent> components;
		std::vector<CollisionEventListener*> listeners;
		void fireEvent(CollisionEvent event);
		
		void processMovementEvent(CollisionComponent* component, MovementEvent event);
		std::vector<MovementEvent> movementEvents;
	
		CollisionComponent* getComponent(int id);

		public:
			CollisionSystem();
			virtual void update (float dt, std::vector<Handle> &handles);
			void addListener(CollisionEventListener* listener);
			Handle addComponent(CollisionComponent component);
			CollisionComponent* getComponent(Handle handle);
			void receiveMovementEvent(MovementEvent event);


	};

}
