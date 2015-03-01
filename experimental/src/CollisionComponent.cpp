#include "CollisionComponent.h"

namespace Soul{

CollisionComponent::CollisionComponent(Model* model){

	for (auto &shape : model->shapes){

		tinyobj::mesh_t mesh = shape.mesh;
		
		for (unsigned int p = 0; p < mesh.positions.size(); p+=3){
			boundingBox.max.x = std::max(mesh.positions[p], boundingBox.max.x);
			boundingBox.max.y = std::max(mesh.positions[p+1], boundingBox.max.y);
			boundingBox.max.z = std::max(mesh.positions[p+2], boundingBox.max.z);
			
			boundingBox.min.x = std::min(mesh.positions[p], boundingBox.min.x);
			boundingBox.min.y = std::min(mesh.positions[p+1], boundingBox.min.y);
			boundingBox.min.z = std::min(mesh.positions[p+2], boundingBox.min.z);
		}
	}

}

}

