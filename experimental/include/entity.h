#ifndef SOUL_ENTITY
#define SOUL_ENTITY

#include <config.h>
#include <cstring>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <tinyobjloader/tiny_obj_loader.h>
#include <misc.h>
#include <boundingbox.h>

namespace Soul { 

class Entity{
	private:
		static unsigned int counter;
	public:
		int id;
		bool visible = true;
		Entity (GLuint vertexarray, std::string inputfile);
		std::vector<Mesh> meshes;
		std::vector<tinyobj::material_t> materials;
		std::vector<Texture> textures;
		glm::mat4 modelMat;
		BoundingBox boundingBox;
		virtual void collision(Entity* other); 
};

class CollectibleObject : public Entity{

	private: 
		int points = 100;
	public:
		CollectibleObject(GLuint vertexarray, std::string inputfile);
		virtual void collision(Entity* other);
		int getPoints(){ return points; };

};

class Player : public Entity{

	private: 
		int points = 0;

	public:
		Player(GLuint vertexarray, std::string inputfile);
		virtual void collision(Entity* other);
		int getPoints(){ return points; };

};

}

#endif
