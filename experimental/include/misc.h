#ifndef SOUL_MISC
#define SOUL_MISC

#include <config.h>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <tinyobjloader/tiny_obj_loader.h>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

namespace Soul { 

GLuint LoadShaders(std::string vertex_file,std::string fragment_file);
GLuint _LoadShaders(std::string vertex_file_path,std::string fragment_file_path);
GLuint loadDDS(std::string imagepath);
GLuint _loadDDS(std::string imagepath);
GLuint loadOBJ(std::string inputfile);
int arrayToVec3(const std::vector<float> vecArray, std::vector<glm::vec3>* vec3Vector);


struct Light{
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 direction = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
};


struct Mesh{
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint elementbuffer;
	int materialId;
	int indices;
	bool bind(GLuint pos, GLuint uv, GLuint normal) const{
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
		   pos,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		   3,                  // size
		   GL_FLOAT,           // type
		   GL_FALSE,           // normalized?
		   0,                  // stride
		   (void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
		    uv,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		    2,                                // size
		    GL_FLOAT,                         // type
		    GL_FALSE,                         // normalized?
		    0,                                // stride
		    (void*)0                          // array buffer offset
		);
				
		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			normal,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

		return true;
	}

};



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

}



#endif
