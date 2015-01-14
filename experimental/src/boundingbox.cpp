#include <boundingbox.h>

namespace Soul{

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
