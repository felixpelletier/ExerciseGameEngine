#include "systems/CollisionSystem.h"
#include "systems/System.h"

namespace Soul{

CollisionSystem::CollisionSystem() : System(){}
void CollisionSystem::update(float dt, std::vector<Handle> &handles){
/*  
	for (auto &handle1 : handles){
		Entity* entity1 = this->entityManager->getEntity(handle1);
		if (handle1.m_type == Entity::Player && entity1->visible){
			BoundingBox bb1 = entity1->collisions.getBoundingBox().transform(entity1->graphics.model.modelMat);
			glm::vec3 center1 = (bb1.min + bb1.max) / 2.0f;
			for (auto &handle2 : handles){
				Entity* entity2 = this->entityManager->getEntity(handle2);
				if (handle2.m_type == Entity::Collectible && entity2->visible && entity1 != entity2){
					BoundingBox bb2 = entity2->collisions.getBoundingBox().transform(entity2->graphics.model.modelMat);

					glm::vec3 center2 = (bb2.min + bb2.max) / 2.0f;

					if(glm::length(center2-center1) < 1.75f){
						
						entity2->visible = false;
						//entity1->collision(entity2);
						//entity2->collision(entity1);

					}		
				}
			}
		}

	}
*/
}
}

