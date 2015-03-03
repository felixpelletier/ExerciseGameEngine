#include "EntityManager.h"
#include "Entity.h"
#include "Handle.h"
#include "GraphicsComponent.h"
#include "CollisionComponent.h"
#include "systems/GraphicSystem.h"
#include "systems/CollisionSystem.h"
#include <string> 

namespace Soul{

EntityManager::EntityManager(CollisionSystem* collisions, GraphicSystem* graphics){

	this->graphic_system = graphics;
	this->collision_system = collisions;

}

Entity* EntityManager::getEntity(Handle handle){
	return &entities[handle.m_index];
}

Handle EntityManager::createEntity(std::string modelPath){

	int model = graphic_system->getModelManager()->loadModel(modelPath);
	Handle graphics = graphic_system->addComponent(GraphicsComponent(model));

	const Model* model_p = graphic_system->getModelManager()->getModel(model);
	std::cout << graphic_system->getModelManager() << std::endl;
	BoundingBox box = BoundingBox(model_p);
	Handle collisions = collision_system->addComponent(CollisionComponent(box));

	Entity entity;
	entity.graphics = graphics;
	entity.collisions = collisions;

	this->entities.push_back(entity);
	Handle handle = Handle(this->entities.size()-1, 0, Handle::Type::Entity);
	return handle;

}

}
