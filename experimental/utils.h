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
struct Entity loadModel(GLuint vertexarray, std::string inputfile);


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
};

struct Texture{
	GLuint diffuse;
	GLuint normal;
};

struct Entity{
	std::vector<Mesh> meshes;
	std::vector<tinyobj::material_t> materials;
	std::vector<Texture> textures;
	glm::mat4 modelMat;
};


