#pragma once

namespace Soul{
	class System{

		public:
			virtual void update (float dt, std::vector<Entity*> entities) = 0;

	};
}
