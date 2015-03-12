#pragma once

#include "Entity.h"
#include "Handle.h"
#include "graphics/GraphicSystem.h"
#include "collisions/CollisionSystem.h"
#include <map>

namespace Soul{

class EntityManager{
	public:
		EntityManager(CollisionSystem* collisions, GraphicSystem* graphics);
		Entity* getEntity(Handle handle);
		Handle createEntity(std::string modelPath);
		Handle createStaticEntity(std::string modelPath);

	private:
		std::map<int, Entity> entities;
		GraphicSystem* graphic_system;
		CollisionSystem* collision_system;
	
};

}
