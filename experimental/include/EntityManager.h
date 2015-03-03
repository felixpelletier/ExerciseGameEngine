#pragma once

#include "Entity.h"
#include "Handle.h"
#include "systems/GraphicSystem.h"
#include "systems/CollisionSystem.h"

namespace Soul{

class EntityManager{
	public:
		EntityManager(CollisionSystem* collisions, GraphicSystem* graphics);
		Entity* getEntity(Handle handle);
		Handle createEntity(std::string modelPath);

	private:
		std::vector<Entity> entities;
		GraphicSystem* graphic_system;
		CollisionSystem* collision_system;
	
};

}
