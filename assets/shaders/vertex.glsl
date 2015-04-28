#version 330 core
in vec3 vertexPos;
in vec2 vertexUV;
in vec3 vertexNormal;
in vec3 vertexOffset;
uniform mat4 projMat;
uniform mat4 viewMat;
uniform mat4 modelMat;
uniform vec3 lightPos;
uniform vec3 lightDir;
uniform vec3 lightColor;

out vec2 UV;
out vec3 lightDir_camspace;
out vec3 normal_camspace;
out vec3 eyeDir_camspace;
out vec3 pos_worldspace;

void main(){
	vec4 pos = vec4(vertexPos + vertexOffset,1);

	gl_Position = projMat * viewMat * modelMat * pos;

	pos_worldspace = (modelMat * pos).xyz;
	
	vec3 pos_camspace = (viewMat * modelMat * pos).xyz;
	eyeDir_camspace = vec3(0,0,0) - pos_camspace;

	vec3 lightPos_camspace = (viewMat * vec4(lightPos, 1)).xyz;
	lightDir_camspace = lightPos_camspace + eyeDir_camspace;

	normal_camspace = (viewMat * modelMat * vec4(vertexNormal,0)).xyz; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.

	UV = vertexUV;
}
