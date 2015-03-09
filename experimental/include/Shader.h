#pragma once

#include <string>
#include <GL/glew.h>


class Shader{
	public:
		static const GLuint s_vertexPosition = 0;
		static const GLuint s_vertexUV = 1;
		static const GLuint s_vertexNormal = 2;
		static const GLuint s_offset = 3;

		GLuint id;
		
		GLuint s_projMat;
		GLuint s_viewMat;
		GLuint s_modelMat;
		
		GLuint s_lightpos;
		GLuint s_lightdir;
		GLuint s_lightcolor;

        	GLuint DiffuseTexID;
        	GLuint NormalTexID;
		
		Shader() {};
		Shader(std::string vertex_file,std::string fragment_file);
	private:
		void loadShaders(std::string vertex_file_path, std::string fragment_file_path);
};
