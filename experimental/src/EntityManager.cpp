#include "EntityManager.h"
#include "Entity.h"
#include "Handle.h"
#include "ModelInstance.h"
#include "GraphicsComponent.h"
#include "CollisionComponent.h"
#include <string> 

namespace Soul{

Entity* EntityManager::getEntity(Handle handle){
	return &entities[handle.m_index];
}

Handle EntityManager::createEntity(Entity::Type type, std::string modelPath){

	int model = modelManager.loadModel(modelPath);
	ModelInstance modelInstance = ModelInstance(model);
	GraphicsComponent graphics = GraphicsComponent(modelInstance);
	CollisionComponent collisions = CollisionComponent(modelManager.getModel(model));
	Entity entity = Entity(graphics, collisions);

	this->entities.push_back(entity);
	Handle handle = Handle(this->entities.size()-1, 0, type);
	return handle;

}

}
