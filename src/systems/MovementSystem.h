#pragma once

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
// glm::translate, glm::rotate, glm::scale
#include <glm/gtc/matrix_transform.hpp>
#include "MovementEventListener.h"
#include "MovementEvent.h"
#include "systems/System.h"

namespace Soul{
class MovementSystem : public System{

	void fireEvent(MovementEvent event);
	std::vector<MovementEventListener*> listeners;

	public:
		MovementSystem();
		virtual void update (float dt, std::vector<Handle> &handles);
		void addListener(MovementEventListener* listener);

		void rotate(Handle h_entity, float orientation, glm::vec3 normal);
		void translate(Handle h_entity, glm::vec3 translation);
		void setToTranslation(Handle h_entity, glm::vec3 translation);
			
	};

};
