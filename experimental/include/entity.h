#ifndef SOUL_ENTITY
#define SOUL_ENTITY

#include <config.h>
#include <cstdint>
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
	public : enum GraphicComponentType {Simple, Instanced}; 
	
	protected:
		static const GraphicComponentType type = Simple;
	public:
		virtual GraphicComponentType getType() { return type; };
		GraphicsComponent() {};
		GraphicsComponent(Model model);
		Model model;
		glm::mat4 modelMat;

};

class InstancedGraphicsComponent : public GraphicsComponent{
		static const GraphicComponentType type = Instanced;
	public:
		InstancedGraphicsComponent() {};
		InstancedGraphicsComponent(Model model, std::vector<glm::vec3> positions);
		std::vector<glm::vec3> positions;
		GLuint instPosBuf;
		unsigned getInstanceCount() {return positions.size();};
		virtual GraphicComponentType getType() { return type; };
};

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
		Entity (GraphicsComponent graphics);
		//static Entity::createEntity;
		GraphicsComponent graphics;
		BoundingBox boundingBox;
		virtual bool isCollidable() {return collidable;};
		virtual void collision(Entity* other); 
};

class CollectibleObject : public Entity{

	private: 
		int points = 100;
		bool collidable = true;
	public:
		CollectibleObject(GraphicsComponent graphics);
		virtual void collision(Entity* other);
		virtual bool isCollidable() {return collidable;};
		int getPoints(){ return points; };

};

class Player : public Entity{

	private: 
		bool collidable = true;
		int points = 0;

	public:
		Player(GraphicsComponent graphics);
		virtual void collision(Entity* other);
		virtual bool isCollidable() {return collidable;};
		int getPoints(){ return points; };

};

struct Handle
{
    Handle() : m_index(0), m_counter(0), m_type(0)
    {}

    Handle(uint32_t index, uint32_t counter, uint32_t type)
        : m_index(index), m_counter(counter), m_type(type)
    {}

    inline operator uint32_t() const;
    
    uint32_t m_index : 12;
    uint32_t m_counter : 15;
    uint32_t m_type : 5;
};

Handle::operator uint32_t() const
{
    return m_type << 27 | m_counter << 12 | m_index;
}


class EntityManager{

	std::vector<Entity> entities;
//	std::vector<Mesh> meshes;
//	std::vector<tinyobj::material_t> materials;
//	std::vector<Texture> textures;
//	std::vector<tinyobj::shape_t> shapes;

	Model loadModel(std::string inputfile);

	public:
		Entity* getEntity(Handle handle);
		Handle createEntity(Entity::Type type, std::string modelPath);
	
};

}

#endif
