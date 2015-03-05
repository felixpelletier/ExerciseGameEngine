#include "systems/CollisionSystem.h"
#include "systems/System.h"
#include "CollisionComponent.h"
#include "CollisionEvent.h"
#include "CollisionEventListener.h"

namespace Soul{

CollisionSystem::CollisionSystem() : System(){}
void CollisionSystem::update(float dt, std::vector<Handle> &handles){

	std::vector<CollisionEvent> events;

	for (auto &pair1 : components){
		CollisionComponent& component1 = pair1.second;
		if (component1.enabled){
		BoundingBox bb1 = component1.getBoundingBox();
		bb1.min += component1.boundingBoxTransform;
		bb1.max += component1.boundingBoxTransform;

			for (auto &pair2 : components){
				CollisionComponent component2 = pair2.second;
				if (component2.enabled && component1.id != component2.id){
					BoundingBox bb2 = component2.getBoundingBox();
					bb2.min += component2.boundingBoxTransform;
					bb2.max += component2.boundingBoxTransform;
					
					glm::vec3 center1 = (bb1.min + bb1.max) / 2.0f;
					glm::vec3 center2 = (bb2.min + bb2.max) / 2.0f;
					
					if(glm::length(center2-center1) < 1.75f){
						
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
		if (event.id1 == 1 || event.id2 == 1)
		std::cout << event.id1 << ":" << event.id2 << std::endl;
		fireEvent(event);
	}

}

void CollisionSystem::addListener(CollisionEventListener* listener){

	listeners.push_back(listener);

}

void CollisionSystem::fireEvent(CollisionEvent event){

	for (auto &listener : listeners){
		listener->fireEvent(event);
	}

}

CollisionComponent* CollisionSystem::getComponent(Handle handle){
	return &components.find(handle.m_index)->second;
}

Handle CollisionSystem::addComponent(CollisionComponent component){

	components.insert(std::pair<int, CollisionComponent> (component.id, component));

	return Handle(component.id, 0, Handle::Type::Collision);


}


}

