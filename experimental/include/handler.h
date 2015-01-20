#pragma once
#include <vector.h>

class HandleManager(){

	private:
		unsigned int counter;
		std::vector<Entity*> handles

	public: 
		int getNewHandle(Entity* entity);
		Entity* getEntity(int id);


};
