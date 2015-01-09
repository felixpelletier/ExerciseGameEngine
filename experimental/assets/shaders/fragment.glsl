#version 330 core
 
// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 lightDir_camspace;
in vec3 normal_camspace;
in vec3 eyeDir_camspace;
 
// Ouput data
out vec3 color;
 
// Values that stay constant for the whole mesh.
uniform sampler2D DiffuseSampler;
uniform sampler2D NormalSampler;
uniform vec3 lightColor;
 
void main(){
 
    vec2 UV_INV = vec2(UV.x, UV.y); //Temporary, necessary for DDS
    // Output color = color of the texture at the specified UV
    vec3 texcolor = texture( DiffuseSampler, UV_INV ).rgb;

    vec3 normal = normalize( normal_camspace );
    vec3 light = normalize( lightDir_camspace );
    vec3 eye = normalize(eyeDir_camspace);
    vec3 ref = reflect(-light,normal);

    float cosTheta = clamp( dot(normal,light), 0, 1 );
    float cosAlpha = clamp( dot(eye,ref), 0, 1 );
    
    float dist = length(lightDir_camspace);

    vec3 ambient = vec3(0.5, 0.5, 0.5);

    vec3 specular = lightColor * pow(cosAlpha,10) * vec3(0.05,0.05,0.05);

    vec3 fogcolor = vec3(0.6, 0.6, 0.65);
    float fogfactor = clamp((eyeDir_camspace.z - 20.0) * 0.01, 0, 1);

    color = ambient * texcolor + (texcolor * lightColor * cosTheta / (dist*dist))
	    + specular;

    color = mix(color, fogcolor, fogfactor);

}
