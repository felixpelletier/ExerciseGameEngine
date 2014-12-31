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
GLuint LoadShaders(std::string vertex_file,std::string fragment_file);
GLuint _LoadShaders(std::string vertex_file_path,std::string fragment_file_path);
GLuint loadDDS(std::string imagepath);
GLuint _loadDDS(std::string imagepath);

const int winWidth = 1024;
const int winHeight = 768;

const GLuint s_vertexPosition = 0;
const GLuint s_vertexUV = 1;
const GLuint s_vertexNormal = 2;

int main()
{
	GLFWwindow* window = initWindow(winWidth, winHeight);

	// Enable depth test
	//glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);

	std::string inputfile = "models/ship.obj";
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err = tinyobj::LoadObj(shapes, materials, inputfile.c_str());

	if (!err.empty()) {
	  std::cerr << err << std::endl;
	  exit(1);
	}

	// Generates a really hard-to-read matrix, but a normal, standard 4x4 matrix nonetheless
	glm::mat4 projMat = glm::perspectiveFov(
	    DEG2RAD(67.0f),         // The horizontal Field of View
	    (float) winWidth,
	    (float) winHeight, // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
	    0.1f,        // Near clipping plane. Keep as big as possible, or you'll get precision issues.
	    100.0f       // Far clipping plane. Keep as little as possible.
	);

	glm::mat4 viewMat = glm::lookAt(
	    glm::vec3(2.0f,1.5f,1.5f), // Camera is at (4,3,3), in World Space
	    glm::vec3(0.0f,0.0f,0.0f), // and looks at the origin
	    glm::vec3(0.0f,1.0f,0.0f)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	tinyobj::mesh_t mesh = shapes[0].mesh;

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.positions.size() * sizeof(float), mesh.positions.data(), GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.texcoords.size() * sizeof(float), mesh.texcoords.data(), GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.normals.size() * sizeof(float), mesh.normals.data(), GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data() , GL_STATIC_DRAW);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "vertex.glsl", "fragment.glsl" );

	glBindAttribLocation(programID, s_vertexPosition, "vertexPos");
	glBindAttribLocation(programID, s_vertexUV, "vertexUV");
	glBindAttribLocation(programID, s_vertexNormal, "vertexNormal");

	// Get a handle for our "MVP" uniform.
	// Only at initialisation time.
	GLuint s_projMat = glGetUniformLocation(programID, "projMat");
	GLuint s_viewMat = glGetUniformLocation(programID, "viewMat");
 
	GLuint Texture = loadDDS("ship.dds");

	// Get a handle for our "myTextureSampler" uniform
        GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
	 
	glUseProgram(programID); 
	
	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.1f, 0.0f);

	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Use our shader
		glUseProgram(programID);

		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		// For each model you render, since the MVP will be different (at least the M part)
		glUniformMatrix4fv(s_projMat, 1, GL_FALSE, &projMat[0][0]);
		glUniformMatrix4fv(s_viewMat, 1, GL_FALSE, &viewMat[0][0]);
		
		// Bind our texture in Texture Unit 0
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, Texture);
                // Set our "myTextureSampler" sampler to user Texture Unit 0
                glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
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
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
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
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			s_vertexNormal,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	 
		// Draw the triangles !
		glDrawElements(
		    GL_TRIANGLES,      // mode
		    mesh.indices.size(),    // count
		    GL_UNSIGNED_INT,   // type
		    nullptr           // element array buffer offset
		); 

		//glDrawArrays(GL_TRIANGLES, 0, mesh.positions.size()/3);

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
	glfwWindowHint(GLFW_SAMPLES, 8); // 4x antialiasing
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



