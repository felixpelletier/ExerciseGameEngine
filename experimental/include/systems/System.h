#pragma once

#include "EntityManager.h"
#include "Handle.h"
#include <vector> 

namespace Soul{
	class System{

		protected:
			EntityManager* entityManager;
		public:
			System(EntityManager* entityManager) {this->entityManager = entityManager;};
			virtual void update (float dt, std::vector<Handle> &handles) = 0;

	};
}
