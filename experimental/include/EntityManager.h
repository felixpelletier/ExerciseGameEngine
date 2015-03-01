#pragma once

#include "ModelManager.h"
#include "Entity.h"
#include "Handle.h"

namespace Soul{

class EntityManager{

	std::vector<Entity> entities;

	public:
		ModelManager modelManager;
		Entity* getEntity(Handle handle);
		Handle createEntity(Entity::Type type, std::string modelPath);
	
};

}
