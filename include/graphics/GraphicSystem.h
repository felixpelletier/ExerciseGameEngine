#pragma once

#include <map>
#include <vector>
#include <array>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
// glm::translate, glm::rotate, glm::scale
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "config.h"
#include "GraphicsComponent.h"
#include "System.h"
#include "Light.h"
#include "Texture.h"
#include "ModelManager.h"
#include "Shader.h"
#include "position/MovementEventListener.h"
#include "position/MovementEvent.h"
#include "scripting/ScriptingEventListener.h"
#include "scripting/ScriptingEvent.h"


namespace Soul{
	class GraphicSystem : public System, public MovementEventListener, public ScriptingEventListener{
		GLFWwindow* initWindow(int width, int height);

		const int winWidth = 1280;
		const int winHeight = 720;

		GLuint VertexArrayID;

		Light light;

		glm::mat4 projMat;

		Shader shader;

		std::array<GraphicsComponent, MAX_ENTITIES> components;
		int highest_element = 0;

		ModelManager modelManager;

		virtual void drawComponent(const GraphicsComponent& component);
		void processMovementEvent(MovementEvent& event);
		void processScriptingEvent(ScriptingEvent& event);

		std::vector<MovementEvent> movementEvents;
		std::vector<ScriptingEvent> scriptingEvents;

		public:
			GraphicSystem();
			GLFWwindow* window;
			glm::vec3 cameraPos;
			glm::mat4 viewMat;
			virtual void update (float dt);
			void receiveMovementEvent(MovementEvent event);
			void receiveScriptingEvent(ScriptingEvent event);
			Handle addComponent(GraphicsComponent component);
			GraphicsComponent* getComponent(Handle handle);
			ModelManager* getModelManager(){return &modelManager;};
			
	};

};
