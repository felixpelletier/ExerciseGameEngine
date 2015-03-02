#pragma once

#include "Handle.h"
#include <vector> 

namespace Soul{
	class System{

		public:
			System() {};
			virtual void update (float dt, std::vector<Handle> &handles) = 0;

	};
}
