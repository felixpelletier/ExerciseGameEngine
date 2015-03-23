#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
// glm::translate, glm::rotate, glm::scale
#include <glm/gtc/matrix_transform.hpp>
#include "MovementEventListener.h"
#include "MovementEvent.h"
#include "PositionComponent.h"
#include "System.h"

namespace Soul{
class PositionSystem : public System{

	void fireEvent(MovementEvent event);
	std::vector<MovementEventListener*> listeners;
	std::map<int, PositionComponent> positions;

	public:
		PositionSystem();
		virtual void update (float dt, std::vector<Handle> &handles);
		void addListener(MovementEventListener* listener);

		void addComponent(PositionComponent component);
		const PositionComponent& getComponent(int id);

		void rotate(Handle h_entity, float orientation, glm::vec3 normal);
		void translate(Handle h_entity, glm::vec3 translation);
		void setToTranslation(Handle h_entity, glm::vec3 translation);
			
	};

};
