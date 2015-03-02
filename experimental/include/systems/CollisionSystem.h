#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Entity.h"
#include "EntityManager.h"
#include "Handle.h"
#include "systems/System.h"

namespace Soul{

	class CollisionSystem : public System{
		public:
			CollisionSystem();
			virtual void update (float dt, std::vector<Handle> &handles);
	};

}
