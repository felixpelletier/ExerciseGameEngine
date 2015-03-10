#include "systems/GraphicSystem.h"

namespace Soul{

GraphicSystem::GraphicSystem() : System(){
	window = initWindow(this->winWidth, this->winHeight);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	// Generates a really hard-to-read matrix, but a normal, standard 4x4 matrix nonetheless
	this->projMat = glm::perspectiveFov(
	    glm::radians(67.0f),         // The horizontal Field of View
	    (float) winWidth,
	    (float) winHeight, // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
	    0.1f,        // Near clipping plane. Keep as big as possible, or you'll get precision issues.
	    200.0f       // Far clipping plane. Keep as little as possible.
	);

	glGenVertexArrays(1, &this->VertexArrayID);
	glBindVertexArray(this->VertexArrayID);

	this->shader = Shader( "vertex.glsl", "fragment.glsl" );

	this->light.position = glm::vec3(-0.0f, 5.0f, 0.0f);
	this->light.direction = glm::vec3(-0.0f, -1.0f, -0.0f);
	this->light.color = glm::vec3(10.0f, 10.0f, 10.0f);

	glUseProgram(this->shader.id); 

	// Dark blue background
	glClearColor(0.6f, 0.6f, 0.65f, 0.0f);

}

void GraphicSystem::receiveMovementEvent(MovementEvent event){
	movementEvents.push_back(event);
}

void GraphicSystem::processMovementEvent(GraphicsComponent* component, MovementEvent event){
	if (event.absolute){
		component->modelMat = glm::mat4();
	}
	
	if (glm::length(event.translation) > 0.00001f)
	component->modelMat = glm::translate(component->modelMat, event.translation);

	if (event.rotation != 0.0f)
		component->modelMat = glm::rotate(component->modelMat, event.rotation, event.rotationAxis);
}

void GraphicSystem::update(float dt, std::vector<Handle> &handles){
		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		// For each model you render, since the MVP will be different (at least the M part)
		glUniformMatrix4fv(shader.s_projMat, 1, GL_FALSE, &this->projMat[0][0]);
		glUniformMatrix4fv(shader.s_viewMat, 1, GL_FALSE, &this->viewMat[0][0]);
		glUniform3fv(shader.s_lightpos, 1, &this->light.position[0]);
		glUniform3fv(shader.s_lightdir, 1, &this->light.direction[0]);
		glUniform3fv(shader.s_lightcolor, 1, &this->light.color[0]);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Use our shader
		glUseProgram(this->shader.id);

		std::cout << movementEvents.size() << std::endl;
		
		for (auto &event : movementEvents){
			GraphicsComponent* component = getComponent(event.id);
			processMovementEvent(component, event);
		}

		movementEvents.clear();

		for (auto &component : components){
			drawComponent(component.second);
		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
}

void GraphicSystem::drawComponent(const GraphicsComponent& component){
	
	glUniformMatrix4fv(shader.s_modelMat, 1, GL_FALSE, &component.modelMat[0][0]);

	Model* model = modelManager.getModel(component.model_id);
	std::vector<Mesh>* meshes = &model->meshes;

	for (auto &mesh : *meshes){
		Texture* texture = &model->textures[mesh.materialId];
		texture->bind(shader.DiffuseTexID, shader.NormalTexID);	
		mesh.bind(shader.s_vertexPosition, shader.s_vertexUV, shader.s_vertexNormal);	
	
		// Draw the triangles !
		glDrawElements(
		    GL_TRIANGLES,      // mode
		    mesh.indices,    // count
		    GL_UNSIGNED_INT,   // type
		    nullptr           // element array buffer offset
		);

	}
}

GraphicsComponent* GraphicSystem::getComponent(Handle handle){
	return getComponent(handle.m_index);
}

GraphicsComponent* GraphicSystem::getComponent(int id){
	return &components.find(id)->second;
}

Handle GraphicSystem::addComponent(GraphicsComponent component){

	components.insert(std::pair<int, GraphicsComponent>(component.id, component));

	return Handle(component.id, 0, Handle::Type::Graphic);

}

GLFWwindow* GraphicSystem::initWindow(int width, int height){
	// Initialise GLFW
	if( !glfwInit() )
	{
	    fprintf( stderr, "Failed to initialize GLFW\n" );
	    return NULL;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 
	 
	// Open a window and create its OpenGL context 
	GLFWwindow* window; // (In the accompanying source code, this variable is global) 
	window = glfwCreateWindow( width, height, "Experiments", NULL, NULL); 
	if( window == NULL ){
	    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
	    glfwTerminate();
	    return NULL;
	}
	glfwMakeContextCurrent(window); // Initialize GLEW 
	glewExperimental=true; // Needed in core profile 
	if (glewInit() != GLEW_OK) {
	    fprintf(stderr, "Failed to initialize GLEW\n");
	    return NULL;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwSwapInterval(1);

	return window;
}

/*  void GraphicSystem::drawMeshInstanced(const GraphicsComponent& graph, const Mesh& mesh) const{

	InstancedGraphicsComponent& igraph = (InstancedGraphicsComponent&) graph;
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, igraph.instPosBuf);
	glVertexAttribPointer(
		this->s_offset,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glVertexAttribDivisor(0, 0); 
	glVertexAttribDivisor(1, 0);
	glVertexAttribDivisor(2, 0); 
	glVertexAttribDivisor(3, 1); 

	// Draw the triangles !
	glDrawElementsInstanced(
	    GL_TRIANGLES,      // mode
	    mesh.indices,    // count
	    GL_UNSIGNED_INT,   // type
	    nullptr,		// element array buffer offset
	    igraph.getInstanceCount() 
	); 

}*/

}
