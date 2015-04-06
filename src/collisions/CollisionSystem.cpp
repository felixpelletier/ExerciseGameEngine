#include "CollisionSystem.h"
#include "System.h"
#include "CollisionComponent.h"
#include "CollisionEvent.h"
#include "CollisionEventListener.h"

namespace Soul{

CollisionSystem::CollisionSystem() : System(){}
void CollisionSystem::update(float dt){

	std::vector<CollisionEvent> events;

	for (auto &event : movementEvents){
		CollisionComponent* component = getComponent(event.id);
		processMovementEvent(component, event);
	}

	movementEvents.clear();

	for (auto &pair1 : components){
		CollisionComponent& component1 = pair1.second;
		if (component1.enabled){
		BoundingBox bb1 = component1.getBoundingBox();
		bb1.min += component1.boundingBoxTransform;
		bb1.max += component1.boundingBoxTransform;
		bb1.center += component1.boundingBoxTransform;

			for (auto &pair2 : components){
				CollisionComponent component2 = pair2.second;
				if (component2.enabled && component1.id != component2.id){
					BoundingBox bb2 = component2.getBoundingBox();
					//bb2.min += component2.boundingBoxTransform;
					//bb2.max += component2.boundingBoxTransform;
					bb2.center += component2.boundingBoxTransform;
					
					if(glm::distance(bb2.center, bb1.center) < 1.75f ){
						CollisionEvent event;
						event.id1 = component1.id;
						event.id2 = component2.id;
						events.push_back(event);

					}

				}

			}
		}

	}

	for (auto i = events.begin(); i != events.end(); ++i){
		bool doubleFound = false;
		for (auto j = i; j != events.end() && !doubleFound; ++j){
			if (i->id1 == j->id2 && i->id2 == j->id1){ 
				i = events.erase(i);
				doubleFound = true;
			}
		}
	}

	for (auto &event : events){
		fireEvent(event);
	}

}

void CollisionSystem::addListener(CollisionEventListener* listener){

	listeners.push_back(listener);

}

void CollisionSystem::fireEvent(CollisionEvent event){

	for (auto &listener : listeners){
		listener->receiveCollisionEvent(event);
	}

}

CollisionComponent* CollisionSystem::getComponent(Handle id){
	return &components.find(id)->second;
}

Handle CollisionSystem::addComponent(CollisionComponent component){

	components.insert(std::pair<int, CollisionComponent> (component.id, component));

	return component.id;


}

void CollisionSystem::receiveMovementEvent(MovementEvent event){
	movementEvents.push_back(event);
}

void CollisionSystem::processMovementEvent(CollisionComponent* component,MovementEvent event){
	if (event.absolute){
		component->boundingBoxTransform = event.translation;
	}
	else{
		component->boundingBoxTransform += event.translation;
	}
}


}

