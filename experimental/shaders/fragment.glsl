#version 330 core
 
// Interpolated values from the vertex shaders
in vec2 UV;
 
// Ouput data
out vec3 color;
 
// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
 
void main(){
 
    vec2 UV_INV = vec2(UV.x, 1.0 - UV.y); //Temporary, necessary for DXT
    // Output color = color of the texture at the specified UV
    color = texture( myTextureSampler, UV_INV ).rgb;
}
