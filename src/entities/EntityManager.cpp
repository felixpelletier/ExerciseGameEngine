#include "entities/EntityManager.h"
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
	this->id_counter = 0;

}

Handle EntityManager::getNewHandle(){
	return id_counter++;
}

Handle EntityManager::createEntity(std::string modelPath){

	Handle entity = getNewHandle();
	//Model loading should not be here.
	int model = graphic_system->getModelManager()->loadModel(modelPath);
	graphic_system->addComponent(GraphicsComponent(entity, model));

	const Model* model_p = graphic_system->getModelManager()->getModel(model);
	BoundingBox box = BoundingBox(model_p);
	collision_system->addComponent(CollisionComponent(entity, box));

	return entity;

}

Handle EntityManager::createStaticEntity(std::string modelPath){

	Handle entity = getNewHandle();
	int model = graphic_system->getModelManager()->loadModel(modelPath);
	graphic_system->addComponent(GraphicsComponent(entity, model));

	return entity;

}

}
