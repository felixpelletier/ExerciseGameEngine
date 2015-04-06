#include "ScriptingSystem.h"

namespace Soul{

ScriptingSystem::ScriptingSystem(EntityManager* entityManager, PositionSystem* mover) :
	System(), entityManager(entityManager), mover(mover){

	L = luaL_newstate();   /* opens Lua */
	luaL_openlibs(L);             /* opens the libraries */

	dofile("scripts/engine.lua");
	dofile("scripts/game.lua");
	

	if (!call("_init", 0, 1)) {
		iterate_events();
	}

}

ScriptingSystem::~ScriptingSystem(){

	lua_close(L);

}

void ScriptingSystem::update(float dt){

	lua_getglobal(L, "_update");
	
	std::cout << "size: " << collisionEvents.size() << std::endl;
	lua_createtable(L, collisionEvents.size(), 0);
	int i = 1;
	for(auto &event : collisionEvents){
		lua_createtable(L, 0, 3);
		lua_pushstring(L, "type");
		lua_pushstring(L, "collision");
		lua_rawset(L, -3);

		lua_pushstring(L, "id1");
		auto id1 = engineToScript.find(event.id1);
		if (id1 != engineToScript.end()){
			lua_pushnumber(L, id1->second);
		}
		else{
			lua_pushnil(L);
		}
		lua_rawset(L, -3);

		lua_pushstring(L, "id2");
		auto id2 = engineToScript.find(event.id2);
		if (id2 != engineToScript.end()){
			lua_pushnumber(L, id2->second);
		}
		else{
			lua_pushnil(L);
		}
		lua_rawset(L, -3);

		lua_rawseti(L, -2, ++i);	
	}
	collisionEvents.clear();

	if(!lua_pcall(L, 1, 1, 0)){
		iterate_events();
	}
	else{
		printError();
	}

}

int ScriptingSystem::call(const char *function, int nargs, int nresults){
	lua_getglobal(L, function);
	if(lua_pcall(L, nargs, nresults, 0)){
		printError();
		return 1;
	}
	return 0;
}

int ScriptingSystem::dofile(const char *file){
	if(luaL_dofile(L, file)){
		printError();
		return 1;
	}
	return 0;
}

void ScriptingSystem::printError(){
	std::cerr <<  lua_tostring(L, -1) << std::endl;
	lua_pop(L, 1);  /* pop error message from the stack */	

}

void ScriptingSystem::iterate_events(){
	lua_pushnil(L);
	while (lua_next(L, -2) != 0) {
		process_event();
		lua_pop(L, 1);
	}
	lua_pop(L, 1);
}

void ScriptingSystem::stackdump_g(lua_State* L)
{
    int i;
    int top = lua_gettop(L);
 
    printf("total in stack %d\n",top);
 
    for (i = 1; i <= top; i++)
    {  /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {
            case LUA_TSTRING:  /* strings */
                printf("string: '%s'\n", lua_tostring(L, i));
                break;
            case LUA_TBOOLEAN:  /* booleans */
                printf("boolean %s\n",lua_toboolean(L, i) ? "true" : "false");
                break;
            case LUA_TNUMBER:  /* numbers */
                printf("number: %g\n", lua_tonumber(L, i));
                break;
            default:  /* other values */
                printf("%s\n", lua_typename(L, t));
                break;
        }
        printf("  ");  /* put a separator */
    }
    printf("\n");  /* end the listing */
}

void ScriptingSystem::process_event(){
	std::string type = getstrfield("type");
	std::cout << type << std::endl;
	if (type == "new_entity"){
		int id = (int)getnumfield("id");
		std::string model = getstrfield("model");
		double x = getnumfield("x");
		double y = getnumfield("y");
		double z = getnumfield("z");
		Handle real_id = entityManager->createEntity(model + ".obj");
		scriptToEngine.insert(std::pair<int, int>(id, real_id));
		engineToScript.insert(std::pair<int, int>(real_id, id));
		mover->setToTranslation(real_id, glm::vec3(x,y,z));
	}
	else if (type == "parameter"){
		ScriptingEvent event;
		event.id = scriptToEngine[(int)getnumfield("id")];
		event.param = getstrfield("key");
		event.value = getstrfield("value");
		std::cout << event.value << std::endl;
		fireEvent(event);
	}
}

std::string ScriptingSystem::getstrfield (const char *key) {
	std::string result;
	lua_pushstring(L, key);
	lua_gettable(L, -2);  /* get dict[key] */
	size_t len;
	const char* cstr = lua_tolstring(L, -1, &len);
	result = std::string(cstr, len);
	lua_pop(L, 1);  /* remove number */
	return result;
}

double ScriptingSystem::getnumfield (const char *key) {
	double result;
	lua_pushstring(L, key);
	lua_gettable(L, -2);  /* get dict[key] */
	result = lua_tonumber(L, -1);
	lua_pop(L, 1);  /* remove number */
	return result;
}

bool ScriptingSystem::getboolfield (const char *key) {
	bool result;
	lua_pushstring(L, key);
	lua_gettable(L, -2);  /* get dict[key] */
	result = lua_toboolean(L, -1);
	lua_pop(L, 1);  /* remove number */
	return result;
}

void ScriptingSystem::addListener(ScriptingEventListener* listener){

	listeners.push_back(listener);

}

void ScriptingSystem::fireEvent(ScriptingEvent event){

	for (auto &listener : listeners){
		listener->receiveScriptingEvent(event);
	}

}

void ScriptingSystem::receiveMovementEvent(MovementEvent event){
	movementEvents.push_back(event);
}

void ScriptingSystem::receiveCollisionEvent(CollisionEvent event){
	collisionEvents.push_back(event);
}

}

