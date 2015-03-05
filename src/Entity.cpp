#include "Entity.h"
#include "Handle.h"

namespace Soul { 

	int Entity::id_counter = 0;
	Entity::Entity(){
		id = id_counter++;
	}

}




