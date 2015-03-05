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
	return &entities.find(handle.m_index)->second;
}

Handle EntityManager::createEntity(std::string modelPath){

	Entity entity;
	int model = graphic_system->getModelManager()->loadModel(modelPath);
	Handle graphics = graphic_system->addComponent(GraphicsComponent(entity.id, model));

	const Model* model_p = graphic_system->getModelManager()->getModel(model);
	std::cout << graphic_system->getModelManager() << std::endl;
	BoundingBox box = BoundingBox(model_p);
	Handle collisions = collision_system->addComponent(CollisionComponent(entity.id, box));

	entity.graphics = graphics;
	entity.collisions = collisions;

	this->entities.insert(std::pair<int, Entity>(entity.id, entity));
	Handle handle = Handle(this->entities.size()-1, 0, Handle::Type::Entity);
	return handle;

}

Handle EntityManager::createStaticEntity(std::string modelPath){

	Entity entity;
	int model = graphic_system->getModelManager()->loadModel(modelPath);
	Handle graphics = graphic_system->addComponent(GraphicsComponent(entity.id, model));

	entity.graphics = graphics;

	this->entities.insert(std::pair<int, Entity>(entity.id, entity));
	Handle handle = Handle(this->entities.size()-1, 0, Handle::Type::Entity);
	return handle;

}

void EntityManager::rotate(Handle h_entity, float orientation, glm::vec3 normal){

	Entity* entity = getEntity(h_entity);
	GraphicsComponent* g_entity = graphic_system->getComponent(entity->graphics);
	g_entity->modelMat = glm::rotate(g_entity->modelMat, orientation, normal);
	//CollisionComponent* c_entity = collision_system->getComponent(entity->collisions);

}

void EntityManager::translate(Handle h_entity, glm::vec3 translation){

	Entity* entity = getEntity(h_entity);
	GraphicsComponent* g_entity = graphic_system->getComponent(entity->graphics);
	g_entity->modelMat = glm::translate(g_entity->modelMat, translation);
	CollisionComponent* c_entity = collision_system->getComponent(entity->collisions);
	c_entity->boundingBoxTransform += translation;

}

void EntityManager::setToTranslation(Handle h_entity, glm::vec3 translation){

	Entity* entity = getEntity(h_entity);
	GraphicsComponent* g_entity = graphic_system->getComponent(entity->graphics);
	glm::mat4x4 mat;
	mat = glm::translate(mat,translation);
	g_entity->modelMat = mat;
	CollisionComponent* c_entity = collision_system->getComponent(entity->collisions);
	c_entity->boundingBoxTransform = translation;

}


}
