#include "BoundingBox.h"
#include "Model.h"
#include "tinyobjloader/tiny_obj_loader.h"

namespace Soul{

	BoundingBox::BoundingBox(const Model* model){
		for (auto &shape : model->shapes){

			tinyobj::mesh_t mesh = shape.mesh;
			
			for (unsigned int p = 0; p < mesh.positions.size(); p+=3){
				max.x = std::max(mesh.positions[p], max.x);
				max.y = std::max(mesh.positions[p+1], max.y);
				max.z = std::max(mesh.positions[p+2], max.z);
				
				min.x = std::min(mesh.positions[p], min.x);
				min.y = std::min(mesh.positions[p+1], min.y);
				min.z = std::min(mesh.positions[p+2], min.z);
			}
		}

	}

	BoundingBox BoundingBox::transform(glm::mat4 matrix){
		
		BoundingBox result;

		glm::vec3 translation = glm::vec3(matrix[3]);
		result.max = max + translation; 
		result.min = min + translation;

		return result;
	}

	bool BoundingBox::intersect(BoundingBox other){

		return( 
			this->max.x > other.min.x &&
			this->min.x < other.max.x &&
			
			this->max.y > other.min.y &&
			this->min.y < other.max.y &&
			
			this->max.z > other.min.z &&
			this->min.z < other.max.z); 

	}

}
