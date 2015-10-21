#pragma once

#include "Handle.h"
#include "graphics/GraphicSystem.h"
#include "collisions/CollisionSystem.h"
#include <map>

namespace Soul{

class EntityManager{
	public:
		EntityManager(CollisionSystem* collisions, GraphicSystem* graphics);
		Handle createEntity(std::string modelPath);
		Handle createStaticEntity(std::string modelPath);

	private:
		GraphicSystem* graphic_system;
		CollisionSystem* collision_system;
		Handle id_counter;
		Handle getNewHandle();
	
};

}
