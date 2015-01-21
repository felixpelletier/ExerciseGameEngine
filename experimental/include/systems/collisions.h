#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <entity.h>
#include <systems/base.h>

namespace Soul{

	class CollisionSystem : public System{
		public:
			CollisionSystem(EntityManager* entityManager);
			virtual void update (float dt, std::vector<Handle> handles);
	};

}
