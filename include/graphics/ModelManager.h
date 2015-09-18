#pragma once

#include <string>
#include <vector>
#include <map>
#include "Model.h"
#include "TextureManager.h"


namespace Soul{

class ModelManager{
	std::map<std::string, GLuint> models_n;
	std::vector<Model> models;
	int _loadModel(std::string path);
	TextureManager textureManager;
	public:
		int loadModel(std::string name);
		Model* getModel(int index);
}; 

}
