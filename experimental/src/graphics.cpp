#include <systems/graphics.h>

namespace Soul{

GraphicSystem::GraphicSystem(EntityManager* entityManager) : System(entityManager){
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
	    500.0f       // Far clipping plane. Keep as little as possible.
	);

	glGenVertexArrays(1, &this->VertexArrayID);
	glBindVertexArray(this->VertexArrayID);

	this->programID = LoadShaders( "vertex.glsl", "fragment.glsl" );

	glBindAttribLocation(this->programID, this->s_vertexPosition, "vertexPos");
	glBindAttribLocation(this->programID, this->s_vertexUV, "vertexUV");
	glBindAttribLocation(this->programID, this->s_vertexNormal, "vertexNormal");
	glBindAttribLocation(this->programID, this->s_offset, "vertexOffset");

	// Get a handle for our "MVP" uniform.
	// Only at initialisation time.
	this->s_projMat = glGetUniformLocation(this->programID, "projMat");
	this->s_viewMat = glGetUniformLocation(this->programID, "viewMat");
	this->s_modelMat = glGetUniformLocation(this->programID, "modelMat");
	
	this->s_lightpos = glGetUniformLocation(this->programID, "lightPos");
	this->s_lightdir = glGetUniformLocation(this->programID, "lightDir");
	this->s_lightcolor = glGetUniformLocation(this->programID, "lightColor");
	
	this->light.position = glm::vec3(-0.0f, 5.0f, 0.0f);
	this->light.direction = glm::vec3(-0.0f, -1.0f, -0.0f);
	this->light.color = glm::vec3(10.0f, 10.0f, 10.0f);
 
	// Get a handle for our "myTextureSampler" uniform
        this->DiffuseTexID  = glGetUniformLocation(programID, "DiffuseSampler");
        this->NormalTexID  = glGetUniformLocation(programID, "NormalSampler");
	 
	glUseProgram(this->programID); 

	// Dark blue background
	glClearColor(0.6f, 0.6f, 0.65f, 0.0f);


}

void GraphicSystem::update(float dt, std::vector<Handle> handles){
		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		// For each model you render, since the MVP will be different (at least the M part)
		glUniformMatrix4fv(this->s_projMat, 1, GL_FALSE, &this->projMat[0][0]);
		glUniformMatrix4fv(this->s_viewMat, 1, GL_FALSE, &this->viewMat[0][0]);
		glUniform3fv(this->s_lightpos, 1, &this->light.position[0]);
		glUniform3fv(this->s_lightdir, 1, &this->light.direction[0]);
		glUniform3fv(this->s_lightcolor, 1, &this->light.color[0]);



		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Use our shader
		glUseProgram(this->programID);

		for (auto const &handle : handles){

			Entity* entity = this->entityManager->getEntity(handle);
			if(entity->visible) this->drawEntity(entity);

		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
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

	return window;
}

void GraphicSystem::drawEntity(Entity* entity){

	GraphicsComponent* graph = &entity->graphics;
	
	glUniformMatrix4fv(s_modelMat, 1, GL_FALSE, &graph->modelMat[0][0]);
	for (auto const &mesh : graph->model.meshes){

		this->drawMesh(graph, mesh);	
		
	}
}

void GraphicSystem::drawMesh(GraphicsComponent* graph, const Mesh& mesh){
	struct Texture texture = graph->model.textures[mesh.materialId];
			
	texture.bind(this->DiffuseTexID, this->NormalTexID);
	mesh.bind(this->s_vertexPosition, this->s_vertexUV, this->s_vertexNormal);	
	
	switch(graph->getType()){
		case GraphicsComponent::Simple:
			this->drawMeshSimple(mesh);	
			break;

		case GraphicsComponent::Instanced:
			this->drawMeshInstanced(graph, mesh);
			break;	

	}

}

void GraphicSystem::drawMeshSimple(const Mesh& mesh){

	// Draw the triangles !
	glDrawElements(
	    GL_TRIANGLES,      // mode
	    mesh.indices,    // count
	    GL_UNSIGNED_INT,   // type
	    nullptr           // element array buffer offset
	);

}
void GraphicSystem::drawMeshInstanced(GraphicsComponent* graph, const Mesh& mesh){

	InstancedGraphicsComponent* igraph = (InstancedGraphicsComponent*) graph;
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, igraph->instPosBuf);
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
	    igraph->getInstanceCount() 
	); 

}

}
