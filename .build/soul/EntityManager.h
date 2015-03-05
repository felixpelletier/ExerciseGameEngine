#pragma once

#include "Entity.h"
#include "Handle.h"
#include "systems/GraphicSystem.h"
#include "systems/CollisionSystem.h"
#include <map>

namespace Soul{

class EntityManager{
	public:
		EntityManager(CollisionSystem* collisions, GraphicSystem* graphics);
		Entity* getEntity(Handle handle);
		Handle createEntity(std::string modelPath);
		Handle createStaticEntity(std::string modelPath);
		void rotate(Handle h_entity, float orientation, glm::vec3 normal);
		void translate(Handle h_entity, glm::vec3 translation);
		void setToTranslation(Handle h_entity, glm::vec3 translation);

	private:
		std::map<int, Entity> entities;
		GraphicSystem* graphic_system;
		CollisionSystem* collision_system;
	
};

}