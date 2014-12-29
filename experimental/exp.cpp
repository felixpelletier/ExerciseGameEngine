#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
// glm::translate, glm::rotate, glm::scale
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

#define DEG2RAD(x) ((x) / 57.295779579f)

//#include <ScriptEngine.h>

#define SHADER_PATH "./shaders/"
#define IMAGES_PATH "./images/"

GLFWwindow* initWindow(int width, int height);
GLuint LoadShaders(std::string vertex_file,std::string fragment_file);
GLuint _LoadShaders(std::string vertex_file_path,std::string fragment_file_path);
GLuint loadDDS(std::string imagepath);
GLuint _loadDDS(std::string imagepath);

const int winWidth = 1024;
const int winHeight = 768;

const GLuint s_vertexPosition = 0;
const GLuint s_vertexUV = 1;

int main()
{
	GLFWwindow* window = initWindow(winWidth, winHeight);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
	    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
	    -1.0f,-1.0f, 1.0f,
	    -1.0f, 1.0f, 1.0f, // triangle 1 : end
	    1.0f, 1.0f,-1.0f, // triangle 2 : begin
	    -1.0f,-1.0f,-1.0f,
	    -1.0f, 1.0f,-1.0f, // triangle 2 : end
	    1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f,-1.0f,
	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f,-1.0f,
	    1.0f,-1.0f,-1.0f,
	    -1.0f,-1.0f,-1.0f,
	    -1.0f,-1.0f,-1.0f,
	    -1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f,-1.0f,
	    1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f,-1.0f,
	    -1.0f, 1.0f, 1.0f,
	    -1.0f,-1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f,-1.0f,
	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f, 1.0f,-1.0f,
	    -1.0f, 1.0f,-1.0f,
	    1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f,-1.0f,
	    -1.0f, 1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f
	};

	// Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.
	static const GLfloat g_uv_buffer_data[] = {
	    0.000059f, 1.0f-0.000004f,
	    0.000103f, 1.0f-0.336048f,
	    0.335973f, 1.0f-0.335903f,
	    1.000023f, 1.0f-0.000013f,
	    0.667979f, 1.0f-0.335851f,
	    0.999958f, 1.0f-0.336064f,
	    0.667979f, 1.0f-0.335851f,
	    0.336024f, 1.0f-0.671877f,
	    0.667969f, 1.0f-0.671889f,
	    1.000023f, 1.0f-0.000013f,
	    0.668104f, 1.0f-0.000013f,
	    0.667979f, 1.0f-0.335851f,
	    0.000059f, 1.0f-0.000004f,
	    0.335973f, 1.0f-0.335903f,
	    0.336098f, 1.0f-0.000071f,
	    0.667979f, 1.0f-0.335851f,
	    0.335973f, 1.0f-0.335903f,
	    0.336024f, 1.0f-0.671877f,
	    1.000004f, 1.0f-0.671847f,
	    0.999958f, 1.0f-0.336064f,
	    0.667979f, 1.0f-0.335851f,
	    0.668104f, 1.0f-0.000013f,
	    0.335973f, 1.0f-0.335903f,
	    0.667979f, 1.0f-0.335851f,
	    0.335973f, 1.0f-0.335903f,
	    0.668104f, 1.0f-0.000013f,
	    0.336098f, 1.0f-0.000071f,
	    0.000103f, 1.0f-0.336048f,
	    0.000004f, 1.0f-0.671870f,
	    0.336024f, 1.0f-0.671877f,
	    0.000103f, 1.0f-0.336048f,
	    0.336024f, 1.0f-0.671877f,
	    0.335973f, 1.0f-0.335903f,
	    0.667969f, 1.0f-0.671889f,
	    1.000004f, 1.0f-0.671847f,
	    0.667979f, 1.0f-0.335851f
	};

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	// Generates a really hard-to-read matrix, but a normal, standard 4x4 matrix nonetheless
	glm::mat4 projMat = glm::perspectiveFov(
	    DEG2RAD(67.0f),         // The horizontal Field of View
	    (float) winWidth,
	    (float) winHeight, // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
	    0.1f,        // Near clipping plane. Keep as big as possible, or you'll get precision issues.
	    100.0f       // Far clipping plane. Keep as little as possible.
	);

	glm::mat4 viewMat = glm::lookAt(
	    glm::vec3(3.0f,3.0f,2.0f), // Camera is at (4,3,3), in World Space
	    glm::vec3(0.0f,0.0f,0.0f), // and looks at the origin
	    glm::vec3(0.0f,1.0f,0.0f)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	 
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	 
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	 
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "vertex.glsl", "fragment.glsl" );

	glBindAttribLocation(programID, s_vertexPosition, "vertexPos");
	glBindAttribLocation(programID, s_vertexUV, "vertexUV");

	// Get a handle for our "MVP" uniform.
	// Only at initialisation time.
	GLuint s_projMat = glGetUniformLocation(programID, "projMat");
	GLuint s_viewMat = glGetUniformLocation(programID, "viewMat");
 
	GLuint Texture = loadDDS("uvtemplate.DDS");

	// Get a handle for our "myTextureSampler" uniform
        GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
	 
	glUseProgram(programID); 
	

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

		// 2nd attribute buffer : colors
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
			 
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 36); // Starting from vertex 0; 3 vertices total -> 1 triangle
		 
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

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

GLuint LoadShaders(std::string vertex_file,std::string fragment_file){
	return _LoadShaders(SHADER_PATH + vertex_file, SHADER_PATH + fragment_file);
}

GLuint _LoadShaders(std::string vertex_file_path,std::string fragment_file_path){
 
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
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
 
    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> ProgramErrorMessage( std::max(InfoLogLength, int(1)) );
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
 
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
 
    return ProgramID;
}

GLuint loadDDS(std::string imagepath){
	return _loadDDS(IMAGES_PATH + imagepath);
}

GLuint _loadDDS(std::string imagepath){

	unsigned char header[124];

	FILE *fp;

	/* try to open the file */
	fp = fopen(imagepath.c_str(), "rb");
	if (fp == NULL)
	return 0;

	/* verify the type of file */
	char filecode[4];
	fread(filecode, 1, 4, fp);
	if (std::strncmp(filecode, "DDS ", 4) != 0) {
	fclose(fp);
	return 0;
	}

	/* get the surface desc */
	fread(&header, 124, 1, fp); 

	unsigned int height      = *(unsigned int*)&(header[8 ]);
	unsigned int width         = *(unsigned int*)&(header[12]);
	unsigned int linearSize     = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC      = *(unsigned int*)&(header[80]);

	unsigned char * buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);
	/* close the file pointer */
	fclose(fp);

	//unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;
	switch(fourCC)
	{
	case FOURCC_DXT1:
	format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	break;
	case FOURCC_DXT3:
	format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	break;
	case FOURCC_DXT5:
	format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	break;
	default:
	free(buffer);
	return 0;
	}

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	/* load the mipmaps */
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
		0, size, buffer + offset);

		offset += size;
		width /= 2;
		height /= 2;
	}
	free(buffer); 

	return textureID;
}


