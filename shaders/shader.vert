#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 vertTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


uniform bool texturePermit;
uniform vec3 lightColor;


out vec3 colorOut;
out vec3 NormalOut;
out vec3 PosFrag;
out vec2 TexCoords;


out SHAD_PAR{
    vec3 fragPos;
    vec3 normal;
    vec2 texCoord;
    vec4 fragPosLight;
} shad_pad;

 
void main()
{
    
    
    gl_Position = projection * view * model * vec4(pos, 1.0);
    PosFrag = vec3(model * vec4(pos, 1.0));
    colorOut = vec3(lightColor);
	
    NormalOut = mat3(transpose(inverse(model))) * Normal;;
	TexCoords = vertTexCoords;    
	
}