#ifndef SOUL_ENTITY
#define SOUL_ENTITY

#include "config.h"
#include <cstdint>
#include <vector>
#include <map>
#include <cstring>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <tinyobjloader/tiny_obj_loader.h>
#include <misc.h>

#include "GraphicsComponent.h"
#include "CollisionComponent.h"

namespace Soul { 

class Entity{
	public: 
		enum Type{
			Standard, Collectible, Player
		};
	private:
		int id;
		bool collidable = false;
	public:
		bool visible = true;
		Entity (GraphicsComponent graphics, CollisionComponent collisions); 
		GraphicsComponent graphics;
		CollisionComponent collisions;
		virtual bool isCollidable() {return collidable;};
		virtual void collision(Entity* other); 
};

}

#endif
