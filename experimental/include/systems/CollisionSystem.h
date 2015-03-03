#pragma once

#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Entity.h"
#include "Handle.h"
#include "CollisionComponent.h"
#include "systems/System.h"

namespace Soul{

	class CollisionSystem : public System{

		std::map<int, CollisionComponent> components;

		public:
			CollisionSystem();
			virtual void update (float dt, std::vector<Handle> &handles);
			Handle addComponent(CollisionComponent component);
			CollisionComponent* getComponent(Handle handle);

	};

}
