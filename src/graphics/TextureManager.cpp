#include "graphics/TextureManager.h"
#include <GL/glew.h>
#include "misc.h"

namespace Soul{

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

}
