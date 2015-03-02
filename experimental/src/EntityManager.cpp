#include "EntityManager.h"
#include "Entity.h"
#include "Handle.h"
#include "GraphicsComponent.h"
#include "CollisionComponent.h"
#include <string> 

namespace Soul{

EntityManager::EntityManager(GraphicSystem* graphics){

	this->graphic_system = graphics;

}

Entity* EntityManager::getEntity(Handle handle){
	return &entities[handle.m_index];
}

Handle EntityManager::createEntity(Entity::Type type, std::string modelPath){

	int model = graphic_system->getModelManager()->loadModel(modelPath);
	Handle graphics = graphic_system->addComponent(GraphicsComponent(model));

	const Model* model_p = graphic_system->getModelManager()->getModel(model);
	std::cout << graphic_system->getModelManager() << std::endl;
	BoundingBox box = BoundingBox(model_p);
	CollisionComponent collisions = CollisionComponent(box);

	Entity entity = Entity(graphics, collisions);

	this->entities.push_back(entity);
	Handle handle = Handle(this->entities.size()-1, 0, type);
	return handle;

}

}
