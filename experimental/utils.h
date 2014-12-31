#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <tinyobjloader/tiny_obj_loader.h>

#define SHADER_PATH "./shaders/"
#define IMAGES_PATH "./images/"

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

GLuint LoadShaders(std::string vertex_file,std::string fragment_file);
GLuint _LoadShaders(std::string vertex_file_path,std::string fragment_file_path);
GLuint loadDDS(std::string imagepath);
GLuint _loadDDS(std::string imagepath);
GLuint loadOBJ(std::string inputfile);
