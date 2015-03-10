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
#include "Shader.h"


namespace Soul{
	class GraphicSystem : public System{
		GLFWwindow* initWindow(int width, int height);

		const int winWidth = 1280;
		const int winHeight = 720;

		GLuint VertexArrayID;

		Light light;

		glm::mat4 projMat;

		Shader shader;

		std::map<int, GraphicsComponent> components;

		ModelManager modelManager;

		virtual void drawComponent(const GraphicsComponent& component);

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
