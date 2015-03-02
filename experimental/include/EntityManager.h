#pragma once

#include "Entity.h"
#include "Handle.h"
#include "systems/GraphicSystem.h"

namespace Soul{

class EntityManager{

	std::vector<Entity> entities;
	GraphicSystem* graphic_system;

	public:
		EntityManager(GraphicSystem* graphics);
		Entity* getEntity(Handle handle);
		Handle createEntity(Entity::Type type, std::string modelPath);
	
};

}
