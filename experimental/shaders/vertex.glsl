#version 330 core
in vec3 vertexPos;
in vec3 vertexColor;
uniform mat4 projMat;
uniform mat4 viewMat;

out vec3 fragmentColor;

void main(){
	vec4 pos = vec4(vertexPos,1);
	gl_Position = projMat * viewMat * pos;

	fragmentColor = vertexColor;
}
