#pragma once

#include <map>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
// glm::translate, glm::rotate, glm::scale
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "Entity.h"
#include "GraphicsComponent.h"
#include "systems/System.h"
#include "Light.h"
#include "Texture.h"
#include "ModelManager.h"


namespace Soul{
	class GraphicSystem : public System{
		GLFWwindow* initWindow(int width, int height);

		const int winWidth = 1280;
		const int winHeight = 720;

		const GLuint s_vertexPosition = 0;
		const GLuint s_vertexUV = 1;
		const GLuint s_vertexNormal = 2;
		const GLuint s_offset = 3;

		GLuint programID;
		GLuint VertexArrayID;

		GLuint s_projMat;
		GLuint s_viewMat;
		GLuint s_modelMat;
		
		GLuint s_lightpos;
		GLuint s_lightdir;
		GLuint s_lightcolor;

		glm::mat4 projMat;

		// Get a handle for our "myTextureSampler" uniform
        	GLuint DiffuseTexID;
        	GLuint NormalTexID;
	 
		//Please make a shader object

		Light light;

		void drawComponent(const GraphicsComponent& graph);

		void drawMeshSimple(const Mesh& mesh);
		void drawMesh(const GraphicsComponent& graph, const Mesh& mesh, const Texture& texture);

		std::map<int, GraphicsComponent> components;

		ModelManager modelManager;

		public:
			GraphicSystem();
			GLFWwindow* window;
			glm::vec3 cameraPos;
			glm::mat4 viewMat;
			virtual void update (float dt, std::vector<Handle> &handles);
			Handle addComponent(GraphicsComponent component);
			GraphicsComponent* getComponent(Handle handle);
			ModelManager* getModelManager(){return &modelManager;};
			
	};

};
