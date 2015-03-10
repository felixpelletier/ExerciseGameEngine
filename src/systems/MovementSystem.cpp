#include "systems/MovementSystem.h"

namespace Soul{

MovementSystem::MovementSystem() : System(){}

void MovementSystem::update(float dt, std::vector<Handle> &handles){

}

void MovementSystem::fireEvent(MovementEvent event){
	for (auto &listener : listeners){
		listener->receiveMovementEvent(event);
	}
}

void MovementSystem::addListener(MovementEventListener* listener){
	listeners.push_back(listener);
}

void MovementSystem::rotate(Handle h_entity, float orientation, glm::vec3 normal){
	
	MovementEvent event;
	event.id = h_entity.m_index;
	event.rotation = orientation;
	event.rotationAxis = normal;
	fireEvent(event);

}

void MovementSystem::translate(Handle h_entity, glm::vec3 translation){

	MovementEvent event;
	event.id = h_entity.m_index;
	event.translation = translation;
	fireEvent(event);

}

void MovementSystem::setToTranslation(Handle h_entity, glm::vec3 translation){

	MovementEvent event;
	event.id = h_entity.m_index;
	event.absolute = true;
	event.translation = translation;
	fireEvent(event);

}


}
