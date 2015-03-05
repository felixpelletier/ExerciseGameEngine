#pragma once

#include <map>
#include <GL/glew.h>

namespace Soul{

	class TextureManager{
	std::map<std::string, GLuint> textures;
	GLuint loadTexture(std::string path);
	public:
		GLuint getTexture(std::string name);

	};

}
