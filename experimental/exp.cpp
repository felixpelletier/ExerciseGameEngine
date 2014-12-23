#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow* initWindow();

int main()
{
	GLFWwindow* window = initWindow();

	do{
	    // Draw nothing, see you in tutorial 2 !
	 
	    // Swap buffers
	    glfwSwapBuffers(window);
	    glfwPollEvents();
	 
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
	glfwWindowShouldClose(window) == 0 );
}

GLFWwindow* initWindow(){
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
	window = glfwCreateWindow( 1024, 768, "Experiments", NULL, NULL); 
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
