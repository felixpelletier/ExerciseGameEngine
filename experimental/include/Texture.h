#pragma once

#include <GL/glew.h>

struct Texture{
	GLuint diffuse;
	GLuint normal;
	bool bind(GLuint DiffuseTexID, GLuint NormalTexID) const{
		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuse);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(DiffuseTexID, 0);

		// Bind our texture in Texture Unit 1
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normal);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(NormalTexID, 1);

		return true;
	}
};
