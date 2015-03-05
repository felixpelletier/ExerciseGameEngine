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
#include "systems/System.h"

namespace Soul{

	class CollisionSystem : public System{

		std::map<int, CollisionComponent> components;
		std::vector<CollisionEventListener*> listeners;
		void fireEvent(CollisionEvent event);

		public:
			CollisionSystem();
			virtual void update (float dt, std::vector<Handle> &handles);
			void addListener(CollisionEventListener* listener);
			Handle addComponent(CollisionComponent component);
			CollisionComponent* getComponent(Handle handle);

	};

}
