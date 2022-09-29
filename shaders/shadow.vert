#version 330 core
layout (location = 0) in vec3 vertpos;
 
uniform mat4 lightSpaceMatrix;
uniform mat4 model;
 
void main()
{
    gl_Position = lightSpaceMatrix * model * vec4(vertpos, 1.0);
}  