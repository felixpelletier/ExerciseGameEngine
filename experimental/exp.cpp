#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
// glm::translate, glm::rotate, glm::scale
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <utils.h>

#define DEG2RAD(x) ((x) / 57.295779579f)

//#include <ScriptEngine.h>

GLFWwindow* initWindow(int width, int height);

const int winWidth = 1280;
const int winHeight = 720;

const GLuint s_vertexPosition = 0;
const GLuint s_vertexUV = 1;
const GLuint s_vertexNormal = 2;

int main()
{
	GLFWwindow* window = initWindow(winWidth, winHeight);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	// Generates a really hard-to-read matrix, but a normal, standard 4x4 matrix nonetheless
	glm::mat4 projMat = glm::perspectiveFov(
	    DEG2RAD(67.0f),         // The horizontal Field of View
	    (float) winWidth,
	    (float) winHeight, // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
	    0.1f,        // Near clipping plane. Keep as big as possible, or you'll get precision issues.
	    100.0f       // Far clipping plane. Keep as little as possible.
	);

	

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	std::vector<Entity> entities;
	entities.push_back(loadModel(VertexArrayID, "ice.obj"));
	entities.push_back(loadModel(VertexArrayID, "Snowmobile.obj"));

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "vertex.glsl", "fragment.glsl" );

	glBindAttribLocation(programID, s_vertexPosition, "vertexPos");
	glBindAttribLocation(programID, s_vertexUV, "vertexUV");
	glBindAttribLocation(programID, s_vertexNormal, "vertexNormal");

	// Get a handle for our "MVP" uniform.
	// Only at initialisation time.
	GLuint s_projMat = glGetUniformLocation(programID, "projMat");
	GLuint s_viewMat = glGetUniformLocation(programID, "viewMat");
	GLuint s_modelMat = glGetUniformLocation(programID, "modelMat");
	
	GLuint s_lightpos = glGetUniformLocation(programID, "lightPos");
	GLuint s_lightdir = glGetUniformLocation(programID, "lightDir");
	GLuint s_lightcolor = glGetUniformLocation(programID, "lightColor");

	Light light;
	light.position = glm::vec3(-0.0f, 5.0f, 0.0f);
	light.direction = glm::vec3(-0.0f, -1.0f, -0.0f);
	light.color = glm::vec3(10.0f, 10.0f, 10.0f);
 
	// Get a handle for our "myTextureSampler" uniform
        GLuint DiffuseTexID  = glGetUniformLocation(programID, "DiffuseSampler");
        GLuint NormalTexID  = glGetUniformLocation(programID, "NormalSampler");
	 
	glUseProgram(programID); 
	
	// Dark blue background
	glClearColor(0.01f, 0.0f, 0.1f, 0.0f);

	double lastTime = glfwGetTime();
	
	glm::vec3 position;
	float orientation = 0.0f;
	do{
		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);
		lastTime = currentTime;

		// Move forward
		if (glfwGetKey(window, GLFW_KEY_UP ) == GLFW_PRESS){
		    position[0] += 6 * deltaTime * glm::sin(orientation);
		    position[2] += 6 * deltaTime * glm::cos(orientation);
		}
		
		if (glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		    position[0] -= 6 * deltaTime * glm::sin(orientation);
		    position[2] -= 6 * deltaTime * glm::cos(orientation);
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		   orientation  += 1.0f * deltaTime;
		}
		
		if (glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		   orientation -= 1.0f * deltaTime;
		}

		glm::mat4 playerMat;
		playerMat = glm::translate(playerMat, position);
		playerMat = glm::rotate(playerMat, orientation, glm::vec3(0.0f, 1.0f, 0.0f));

		entities[1].modelMat = playerMat;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Use our shader
		glUseProgram(programID);

		glm::vec3 cameraPos = glm::vec3(position);
		cameraPos.y = 3.0f;
		cameraPos.x -= 6.0f * glm::sin(orientation);
		cameraPos.z -= 6.0f * glm::cos(orientation);

		glm::mat4 viewMat = glm::lookAt(
		    cameraPos, // Camera is at (4,3,3), in World Space
		    position, // and looks at the origin
		    glm::vec3(0.0f,1.0f,0.0f)  // Head is up (set to 0,-1,0 to look upside-down)
		);

		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		// For each model you render, since the MVP will be different (at least the M part)
		glUniformMatrix4fv(s_projMat, 1, GL_FALSE, &projMat[0][0]);
		glUniformMatrix4fv(s_viewMat, 1, GL_FALSE, &viewMat[0][0]);
		glUniform3fv(s_lightpos, 1, &light.position[0]);
		glUniform3fv(s_lightdir, 1, &light.direction[0]);
		glUniform3fv(s_lightcolor, 1, &light.color[0]);
		
		for (auto const &entity : entities){
			for (auto const &mesh : entity.meshes){
				
				glUniformMatrix4fv(s_modelMat, 1, GL_FALSE, &entity.modelMat[0][0]);

				struct Texture texture = entity.textures[mesh.materialId];
				// Bind our texture in Texture Unit 0
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture.diffuse);
				// Set our "myTextureSampler" sampler to user Texture Unit 0
				glUniform1i(DiffuseTexID, 0);

				// Bind our texture in Texture Unit 1
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, texture.normal);
				// Set our "myTextureSampler" sampler to user Texture Unit 0
				glUniform1i(NormalTexID, 1);

				// 1rst attribute buffer : vertices
				glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, mesh.vertexbuffer);
				glVertexAttribPointer(
				   s_vertexPosition,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				   3,                  // size
				   GL_FLOAT,           // type
				   GL_FALSE,           // normalized?
				   0,                  // stride
				   (void*)0            // array buffer offset
				);

				// 2nd attribute buffer : UVs
				glEnableVertexAttribArray(1);
				glBindBuffer(GL_ARRAY_BUFFER, mesh.uvbuffer);
				glVertexAttribPointer(
				    s_vertexUV,                                // attribute. No particular reason for 1, but must match the layout in the shader.
				    2,                                // size
				    GL_FLOAT,                         // type
				    GL_FALSE,                         // normalized?
				    0,                                // stride
				    (void*)0                          // array buffer offset
				);
						
				// 3rd attribute buffer : normals
				glEnableVertexAttribArray(2);
				glBindBuffer(GL_ARRAY_BUFFER, mesh.normalbuffer);
				glVertexAttribPointer(
					s_vertexNormal,                                // attribute
					3,                                // size
					GL_FLOAT,                         // type
					GL_FALSE,                         // normalized?
					0,                                // stride
					(void*)0                          // array buffer offset
				);

				// Index buffer
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.elementbuffer);
			 
				// Draw the triangles !
				glDrawElements(
				    GL_TRIANGLES,      // mode
				    mesh.indices,    // count
				    GL_UNSIGNED_INT,   // type
				    nullptr           // element array buffer offset
				); 

				//std::cout << glGetError() << "\n";

			}
		}
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	 
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
	glfwWindowShouldClose(window) == 0 );
}

GLFWwindow* initWindow(int width, int height){
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





