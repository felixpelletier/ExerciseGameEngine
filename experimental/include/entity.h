#ifndef SOUL_ENTITY
#define SOUL_ENTITY

#include <config.h>
#include <vector>
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

class GraphicsComponent{
	public:
		enum GraphicComponentType {Simple, Instanced}; 
	
	protected:
		static const GraphicComponentType type = Simple;
	public:
		virtual GraphicComponentType getType() { return type; };
		GraphicsComponent() {};
		GraphicsComponent(GLuint VertexArrayID, std::string inputfile);
		std::vector<Mesh> meshes;
		std::vector<tinyobj::material_t> materials;
		std::vector<Texture> textures;
		std::vector<tinyobj::shape_t> shapes;
		glm::mat4 modelMat;

};

class InstancedGraphicsComponent : public GraphicsComponent{
		static const GraphicComponentType type = Instanced;
	public:
		InstancedGraphicsComponent() {};
		InstancedGraphicsComponent(GLuint VertexArrayID, std::string inputfile, std::vector<glm::vec3> positions);
		std::vector<glm::vec3> positions;
		GLuint instPosBuf;
		unsigned getInstanceCount() {return positions.size();};
		virtual GraphicComponentType getType() { return type; };
};

class Entity{
	private:
		static unsigned int counter;
		int id;
		bool collidable = false;
	public:
		bool visible = true;
		Entity (std::string inputfile);
		//static Entity::createEntity;
		GraphicsComponent* graphics;
		BoundingBox boundingBox;
		virtual bool isCollidable() {return collidable;};
		virtual void collision(Entity* other); 
};

class CollectibleObject : public Entity{

	private: 
		int points = 100;
		bool collidable = true;
	public:
		CollectibleObject(std::string inputfile);
		virtual void collision(Entity* other);
		virtual bool isCollidable() {return collidable;};
		int getPoints(){ return points; };

};

class Player : public Entity{

	private: 
		bool collidable = true;
		int points = 0;

	public:
		Player(std::string inputfile);
		virtual void collision(Entity* other);
		virtual bool isCollidable() {return collidable;};
		int getPoints(){ return points; };

};

}

#endif
