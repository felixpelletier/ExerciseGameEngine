#version 330 core
in vec3 vertexpos;
uniform mat4 projMat;
uniform mat4 viewMat;

void main(){
	vec4 pos = vec4(vertexpos,1);
	gl_Position = projMat * viewMat * pos;
}
