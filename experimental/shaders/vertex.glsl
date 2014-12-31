#version 330 core
in vec3 vertexPos;
in vec2 vertexUV;
in vec2 vertexNormal;
uniform mat4 projMat;
uniform mat4 viewMat;

out vec2 UV;

void main(){
	vec4 pos = vec4(vertexPos,1);
	gl_Position = projMat * viewMat * pos;

	UV = vertexUV;
}
