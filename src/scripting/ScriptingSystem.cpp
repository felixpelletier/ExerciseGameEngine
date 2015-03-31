#include "ScriptingSystem.h"

namespace Soul{

ScriptingSystem::ScriptingSystem() : System(){

	L = luaL_newstate();   /* opens Lua */
	luaL_openlibs(L);             /* opens the libraries */

	dofile(L, "scripts/engine.lua");
	dofile(L, "scripts/game.lua");

}

ScriptingSystem::~ScriptingSystem(){

	lua_close(L);

}

void ScriptingSystem::update(float dt){

	if (!call(L, "update", 0, 1)) {
		iterate_events(L);
	}

}

int ScriptingSystem::call(lua_State* L, const char *function, int nargs, int nresults){
	lua_getglobal(L, function);
	if(lua_pcall(L, nargs, nresults, 0)){
		printError(L);
		return 1;
	}
	return 0;
}

int ScriptingSystem::dofile(lua_State* L, const char *file){
	if(luaL_dofile(L, file)){
		printError(L);
		return 1;
	}
	return 0;
}

void ScriptingSystem::printError(lua_State *L){
	std::cerr <<  lua_tostring(L, -1) << std::endl;
	lua_pop(L, 1);  /* pop error message from the stack */	

}

void ScriptingSystem::iterate_events(lua_State* L){
	lua_pushnil(L);
	while (lua_next(L, -2) != 0) {
		process_event(L);
	}
}

void ScriptingSystem::process_event(lua_State* L){
	std::string type = getfield(L, "type");
	std::cout << type << std::endl;
	lua_pop(L, 1);
}

std::string ScriptingSystem::getfield (lua_State *L, const char *key) {
	std::string result;
	lua_pushstring(L, key);
	lua_gettable(L, -2);  /* get dict[key] */
	size_t len;
	const char* cstr = lua_tolstring(L, -1, &len);
	result = std::string(cstr, len);
	lua_pop(L, 1);  /* remove number */
	return result;
}

void ScriptingSystem::addListener(ScriptingEventListener* listener){

	listeners.push_back(listener);

}

void ScriptingSystem::fireEvent(ScriptingEvent event){

	for (auto &listener : listeners){
		listener->fireEvent(event);
	}

}

void ScriptingSystem::receiveMovementEvent(MovementEvent event){
	movementEvents.push_back(event);
}

void ScriptingSystem::receiveCollisionEvent(CollisionEvent event){
	collisionEvents.push_back(event);
}

}

