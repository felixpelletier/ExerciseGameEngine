#include "graphics/Shader.h"
#include "config.h" 
#include <fstream>
#include <iostream>
#include <vector>

Shader::Shader(std::string vertex_file, std::string fragment_file){
	loadShaders(SHADER_PATH + vertex_file, SHADER_PATH + fragment_file);
}

void Shader::loadShaders(std::string vertex_file_path,std::string fragment_file_path){
 
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open())
	{
	std::string Line = "";
	while(getline(VertexShaderStream, Line))
	    VertexShaderCode += "\n" + Line;
	VertexShaderStream.close();
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
	std::string Line = "";
	while(getline(FragmentShaderStream, Line))
	    FragmentShaderCode += "\n" + Line;
	FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	std::cout << "Compiling shader : " << vertex_file_path << "\n";
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

	// Compile Fragment Shader
	std::cout << "Compiling shader : " << fragment_file_path << "\n";
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

	// Link the program
	fprintf(stdout, "Linking program\n");
	id = glCreateProgram();
	glAttachShader(id, VertexShaderID);
	glAttachShader(id, FragmentShaderID);
	glLinkProgram(id);

	// Check the program
	glGetProgramiv(id, GL_LINK_STATUS, &Result);
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage( std::max(InfoLogLength, int(1)) );
	glGetProgramInfoLog(id, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

    	glBindAttribLocation(this->id, this->s_vertexPosition, "vertexPos");
	glBindAttribLocation(this->id, this->s_vertexUV, "vertexUV");
	glBindAttribLocation(this->id, this->s_vertexNormal, "vertexNormal");
	glBindAttribLocation(this->id, this->s_offset, "vertexOffset");

	// Get a handle for our "MVP" uniform.
	// Only at initialisation time.
	this->s_projMat = glGetUniformLocation(this->id, "projMat");
	this->s_viewMat = glGetUniformLocation(this->id, "viewMat");
	this->s_modelMat = glGetUniformLocation(this->id, "modelMat");
	
	this->s_lightpos = glGetUniformLocation(this->id, "lightPos");
	//this->s_lightdir = glGetUniformLocation(this->id, "lightDir");
	this->s_lightcolor = glGetUniformLocation(this->id, "lightColor");
	
	// Get a handle for our "myTextureSampler" uniform
        this->DiffuseTexID  = glGetUniformLocation(id, "DiffuseSampler");
        this->NormalTexID  = glGetUniformLocation(id, "NormalSampler");
 
}
