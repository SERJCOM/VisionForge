#version 330 core
layout (location = 0) in vec3 vertpos;
 
uniform mat4 lightSpaceMatrix;
uniform mat4 model;
 
void main()
{
    gl_Position = lightSpaceMatrix * model * vec4(vertpos, 1.0);
	//gl_Position = model * vec4(vertpos, 1.0);
	
	//gl_Position = vec4(vertpos.x, vertpos.y, 0.1, 1.0);
}  