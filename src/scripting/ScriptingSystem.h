#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <string>
#include "entities/Entity.h"
#include "entities/EntityManager.h"
#include "Handle.h"
#include "ScriptingEvent.h"
#include "ScriptingEventListener.h"

#include "collisions/CollisionComponent.h"
#include "collisions/CollisionEvent.h"
#include "collisions/CollisionEventListener.h"
#include "position/PositionSystem.h"
#include "position/MovementEventListener.h"
#include "position/MovementEvent.h"
#include "System.h"
#include "lua.hpp"

namespace Soul{

	class ScriptingSystem : public System, public MovementEventListener, public CollisionEventListener{

		std::vector<ScriptingEventListener*> listeners;
		void fireEvent(ScriptingEvent event);
		
		std::vector<MovementEvent> movementEvents;
		std::vector<CollisionEvent> collisionEvents;

		std::map<int, int> scriptToEngine;
		std::map<int, int> engineToScript;

		std::string getstrfield (const char *key);
		double getnumfield (const char *key);
		bool getboolfield (const char *key);
		void iterate_events();
		int dofile(const char *file);
		int call(const char *function, int nargs, int nresults);
		void printError();
		void process_event();

		lua_State* L;

		EntityManager* entityManager;
		PositionSystem* mover;

		void stackdump_g(lua_State* L);

		void dumpCollisionsEventsToStack();
	
		public:
			ScriptingSystem(EntityManager* entityManager, PositionSystem* mover);
			~ScriptingSystem();
			virtual void update (float dt);
			void addListener(ScriptingEventListener* listener);
			void receiveMovementEvent(MovementEvent event);
			void receiveCollisionEvent(CollisionEvent event);


	};

}
