#include <systems/collisions.h>

namespace Soul{
void CollisionSystem::update(float dt, std::vector<Entity*> entities){
	for (auto &entity1 : entities){
		if (entity1->isCollidable() && entity1->visible){
			BoundingBox bb1 = entity1->boundingBox.transform(entity1->graphics->modelMat);
			glm::vec3 center1 = (bb1.min + bb1.max) / 2.0f;
			for (auto &entity2 : entities){
				if (entity2->isCollidable() && entity2->visible && entity1 != entity2){
					BoundingBox bb2 = entity2->boundingBox.transform(entity2->graphics->modelMat);

					glm::vec3 center2 = (bb2.min + bb2.max) / 2.0f;

					std::cout << center1.y <<"\n";
					if(glm::length(center2-center1) < 1.75f){

						entity1->collision(entity2);
						entity2->collision(entity1);

					}		
				}
			}
		}

	}
}
}

