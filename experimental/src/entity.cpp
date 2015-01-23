#include <entity.h>

namespace Soul { 

GraphicsComponent::GraphicsComponent(ModelInstance model){

	this->model = model;

}

InstancedGraphicsComponent::InstancedGraphicsComponent(ModelInstance model, std::vector<glm::vec3> positions)
: GraphicsComponent(model)
{
	this->positions = positions;

	glGenBuffers(1, &instPosBuf);
	glBindBuffer(GL_ARRAY_BUFFER, instPosBuf);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);
	
}




//unsigned int Entity::counter = 0;

Entity::Entity(GraphicsComponent graphics, ModelManager modelManager){

	this->graphics = graphics;

	for (auto &shape : modelManager.getModel(this->graphics.model.model)->shapes){

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

CollectibleObject::CollectibleObject(GraphicsComponent graphics, ModelManager modelManager) : Entity::Entity(graphics, modelManager){}

void CollectibleObject::collision(Entity* other){

	this->visible = false;

}

Player::Player(GraphicsComponent graphics, ModelManager modelManager) : Entity::Entity(graphics, modelManager){}

void Player::collision(Entity* other){

	CollectibleObject* collect = (CollectibleObject*) other;
	points += collect->getPoints(); 

	std::cout << points << " points\n";

}

Entity* EntityManager::getEntity(Handle handle){
	return &entities[handle.m_index];
}

Handle EntityManager::createEntity(Entity::Type type, std::string modelPath){

	int model = modelManager.loadModel(modelPath);
	ModelInstance modelInstance = ModelInstance(model);
	GraphicsComponent graphics = GraphicsComponent(modelInstance);
	Entity entity = Entity(graphics, this->modelManager);

	this->entities.push_back(entity);
	Handle handle = Handle(this->entities.size()-1, 0, type);
	return handle;

}

GLuint TextureManager::getTexture(std::string name){

	auto i_texture = textures.find(name);
	if (i_texture == textures.end()){
		return loadTexture(name);	
	}
	else{
		return (*i_texture).second;
	}
}

GLuint TextureManager::loadTexture(std::string path){

	GLuint texture = loadDDS(path);

	textures.insert(std::pair<std::string, GLuint>(path, texture)); 
	
	return texture;
}

int ModelManager::loadModel(std::string name){

	auto i_model = models_n.find(name);
	if (i_model == models_n.end()){
		return _loadModel(name);	
	}
	else{
		return (*i_model).second;
	}
}

Model* ModelManager::getModel(int index){
	return &models[index];
}

int ModelManager::_loadModel(std::string inputfile){

	Model model;

	inputfile = MODELS_PATH + inputfile;

	std::vector<tinyobj::material_t> materials;

	std::string err = tinyobj::LoadObj(model.shapes, materials, inputfile.c_str(), MODELS_PATH);

	if (!err.empty()) {
	  std::cerr << err << std::endl;
	  exit(1);
	}

	model.meshes.reserve(model.shapes.size());
	model.textures.reserve(materials.size());

	for (auto &material : materials){
		 struct Texture texture;
		 texture.diffuse = loadDDS(material.diffuse_texname); //Shall be changed
		 texture.normal = loadDDS(material.normal_texname);
		 model.textures.push_back(texture);
	}

	for (auto &shape : model.shapes){
	
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
		
		model.meshes.push_back(newmesh);
	}

	models.push_back(model);
	models_n.insert(std::pair<std::string, int>(inputfile, models.size() - 1)); 
	
	return models.size() - 1; 

}


}




