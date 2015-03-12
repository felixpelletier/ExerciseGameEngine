#include "ModelManager.h"
#include "config.h"
#include <iostream>

namespace Soul{

int ModelManager::loadModel(std::string name){
	
	auto i_model = models_n.find(MODELS_PATH + name);
	if (i_model == models_n.end()){
		std::cout << "gotta load" << std::endl;
		return _loadModel(name);	
	}
	else{
		std::cout << "found it!" << std::endl;
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
		 texture.diffuse = this->textureManager.getTexture(material.diffuse_texname);
		 texture.normal = this->textureManager.getTexture(material.normal_texname);
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
