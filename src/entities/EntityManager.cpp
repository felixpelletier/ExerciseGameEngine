#include "entities/EntityManager.h"
#include "entities/Entity.h"
#include "Handle.h"
#include "graphics/GraphicsComponent.h"
#include "collisions/CollisionComponent.h"
#include "graphics/GraphicSystem.h"
#include "collisions/CollisionSystem.h"
#include <string> 

namespace Soul{

EntityManager::EntityManager(CollisionSystem* collisions, GraphicSystem* graphics){

	this->graphic_system = graphics;
	this->collision_system = collisions;

}

Entity* EntityManager::getEntity(Handle handle){
	return &entities.find(handle)->second;
}

Handle EntityManager::createEntity(std::string modelPath){

	Entity entity;
	int model = graphic_system->getModelManager()->loadModel(modelPath);
	int graphics = graphic_system->addComponent(GraphicsComponent(entity.id, model));

	const Model* model_p = graphic_system->getModelManager()->getModel(model);
	BoundingBox box = BoundingBox(model_p);
	int collisions = collision_system->addComponent(CollisionComponent(entity.id, box));

	//entity.graphics = graphics;
	//entity.collisions = collisions;

	this->entities.insert(std::pair<int, Entity>(entity.id, entity));
	Handle handle = entity.id;
	return handle;

}

Handle EntityManager::createStaticEntity(std::string modelPath){

	Entity entity;
	int model = graphic_system->getModelManager()->loadModel(modelPath);
	Handle graphics = graphic_system->addComponent(GraphicsComponent(entity.id, model));

	entity.graphics = graphics;

	this->entities.insert(std::pair<int, Entity>(entity.id, entity));
	Handle handle = entity.id;
	return handle;

}

}
