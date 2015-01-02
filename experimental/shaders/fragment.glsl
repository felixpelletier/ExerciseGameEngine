#version 330 core
 
// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 lightDir_camspace;
in vec3 normal_camspace;
 
// Ouput data
out vec3 color;
 
// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform vec3 lightColor;
 
void main(){
 
    vec2 UV_INV = vec2(UV.x, UV.y); //Temporary, necessary for DDS
    // Output color = color of the texture at the specified UV
    vec3 texcolor = texture( myTextureSampler, UV_INV ).rgb;

    vec3 n = normalize( normal_camspace );
    vec3 l = normalize( lightDir_camspace );
    float cosTheta = clamp( dot(n,l), 0, 1 );
    float dist = length(lightDir_camspace);

    vec3 ambiant = vec3(0.1, 0.1, 0.1);

    color = ambiant + (texcolor * lightColor * cosTheta / (dist*dist));
}
