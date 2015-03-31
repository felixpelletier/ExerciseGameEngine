#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <string>
#include "entities/Entity.h"
#include "Handle.h"
#include "ScriptingEvent.h"
#include "ScriptingEventListener.h"

#include "collisions/CollisionComponent.h"
#include "collisions/CollisionEvent.h"
#include "collisions/CollisionEventListener.h"
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

		std::string getfield (lua_State *L, const char *key);
		void iterate_events(lua_State* L);
		int dofile(lua_State* L, const char *file);
		int call(lua_State* L, const char *function, int nargs, int nresults);
		void printError(lua_State *L);
		void process_event(lua_State* L);

		lua_State* L;
	
		public:
			ScriptingSystem();
			~ScriptingSystem();
			virtual void update (float dt);
			void addListener(ScriptingEventListener* listener);
			void receiveMovementEvent(MovementEvent event);
			void receiveCollisionEvent(CollisionEvent event);


	};

}
