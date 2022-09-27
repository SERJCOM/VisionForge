#version 330 core
layout (location = 0) in vec3 vertpos;
 
uniform mat4 shadowmatrix;
uniform mat4 model;
 
void main()
{
    gl_Position = shadowmatrix * model * vec4(vertpos, 1.0);
}  