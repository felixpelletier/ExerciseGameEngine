#include "PositionSystem.h"

namespace Soul{

PositionSystem::PositionSystem() : System(){}

void PositionSystem::update(float dt, std::vector<Handle> &handles){

}

void PositionSystem::addComponent(PositionComponent component){

	positions.insert(std::pair<int, PositionComponent>(component.id, component));

}

const PositionComponent& PositionSystem::getComponent(int id){
	return *_getComponent(id);
}

PositionComponent* PositionSystem::_getComponent(int id){
	return &positions.find(id)->second;
}

void PositionSystem::fireEvent(MovementEvent event){
	for (auto &listener : listeners){
		listener->receiveMovementEvent(event);
	}
}

void PositionSystem::addListener(MovementEventListener* listener){
	listeners.push_back(listener);
}

void PositionSystem::rotate(Handle h_entity, float orientation, glm::vec3 normal){
	
	MovementEvent event;
	event.id = h_entity.m_index;
	event.rotation = orientation;
	event.rotationAxis = normal;
	fireEvent(event);

}

void PositionSystem::translate(Handle h_entity, glm::vec3 translation){

	int id = h_entity.m_index;
	PositionComponent* component = _getComponent(id);
	component->position += translation;

	MovementEvent event;
	event.id = h_entity.m_index;
	event.translation = translation;
	fireEvent(event);

}

void PositionSystem::setToTranslation(Handle h_entity, glm::vec3 translation){

	int id = h_entity.m_index;
	PositionComponent* component = _getComponent(id);
	component->position = translation;

	MovementEvent event;
	event.id = h_entity.m_index;
	event.absolute = true;
	event.translation = translation;
	fireEvent(event);

}


}
