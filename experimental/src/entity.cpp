#include <entity.h>

namespace Soul { 

GraphicsComponent::GraphicsComponent(GLuint VertexArrayID, std::string inputfile){

	//glBindVertexArray(VertexArrayID);

	inputfile = MODELS_PATH + inputfile;

	std::string err = tinyobj::LoadObj(shapes, this->materials, inputfile.c_str(), MODELS_PATH);

	if (!err.empty()) {
	  std::cerr << err << std::endl;
	  exit(1);
	}

	this->meshes.reserve(shapes.size());
	this->textures.reserve(this->materials.size());

	for (auto &material : this->materials){
		 struct Texture texture;
		 texture.diffuse = loadDDS(material.diffuse_texname);
		 texture.normal = loadDDS(material.normal_texname);
		 this->textures.push_back(texture);
	}

	for (auto &shape : shapes){
	
		tinyobj::mesh_t mesh = shape.mesh;

		struct Mesh newmesh;

		newmesh.materialId = mesh.material_ids[0];
		newmesh.indices = mesh.indices.size();
		
		glGenBuffers(1, &newmesh.vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, newmesh.vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, mesh.positions.size() * sizeof(float), mesh.positions.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &newmesh.uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, newmesh.uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, mesh.texcoords.size() * sizeof(float), mesh.texcoords.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &newmesh.normalbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, newmesh.normalbuffer);
		glBufferData(GL_ARRAY_BUFFER, mesh.normals.size() * sizeof(float), mesh.normals.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &newmesh.elementbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newmesh.elementbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data() , GL_STATIC_DRAW);
		
		this->meshes.push_back(newmesh);
	}


}

InstancedGraphicsComponent::InstancedGraphicsComponent(GLuint VertexArrayID, std::string inputfile, std::vector<glm::vec3> positions)
: GraphicsComponent(VertexArrayID, inputfile)
{
	this->positions = positions;

	glGenBuffers(1, &instPosBuf);
	glBindBuffer(GL_ARRAY_BUFFER, instPosBuf);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);
	
}




unsigned int Entity::counter = 0;

Entity::Entity(std::string inputfile){

	this->id = this->counter++;
	this->graphics = new GraphicsComponent(0, inputfile);

	for (auto &shape : graphics->shapes){

		tinyobj::mesh_t mesh = shape.mesh;
		
		for (unsigned int p = 0; p < mesh.positions.size(); p+=3){
			boundingBox.max.x = std::max(mesh.positions[p], boundingBox.max.x);
			boundingBox.max.y = std::max(mesh.positions[p+1], boundingBox.max.y);
			boundingBox.max.z = std::max(mesh.positions[p+2], boundingBox.max.z);
			
			boundingBox.min.x = std::min(mesh.positions[p], boundingBox.min.x);
			boundingBox.min.y = std::min(mesh.positions[p+1], boundingBox.min.y);
			boundingBox.min.z = std::min(mesh.positions[p+2], boundingBox.min.z);
		}
	}

	
}

void Entity::collision(Entity* other){

}

CollectibleObject::CollectibleObject(std::string inputfile) : Entity::Entity(inputfile){}

void CollectibleObject::collision(Entity* other){

	this->visible = false;

}

Player::Player(std::string inputfile) : Entity::Entity(inputfile){}

void Player::collision(Entity* other){

	CollectibleObject* collect = (CollectibleObject*) other;
	if (other->visible){
		points += collect->getPoints(); 
	}

	std::cout << points << " points\n";

}


}




