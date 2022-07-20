#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 vertTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


uniform bool texturePermit;
uniform vec3 lightColor;
uniform vec3 PickingColor;

out vec3 colorOut;
out vec3 NormalOut;
out vec3 PosFrag;
out vec2 TexCoords;

 
void main()
{
    
    gl_Position = projection * view * model * vec4(pos, 1.0);
    PosFrag = vec3(model * vec4(pos, 1.0));
    colorOut = vec3(lightColor);
    NormalOut = Normal;
	TexCoords = vertTexCoords;    
	
}