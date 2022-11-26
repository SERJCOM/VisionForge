#version 430 core
#extension GL_ARB_shader_storage_buffer_object : require

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 vertTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;
uniform int NUMBER_LIGHT;


out vec3 colorOut; // color 
out vec3 NormalOut; // normal
out vec3 PosFrag; // position of the fragment without matrix projection and view
out vec2 TexCoords; // texture coordinates 
out vec4 fragPosLight; // position of the fragment from the side of the shadow source

 
void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0);
	
    PosFrag = vec3(model * vec4(pos, 1.0));
	fragPosLight = lightSpaceMatrix * vec4(PosFrag, 1.0); // for shadows
	
    NormalOut = mat3(transpose(inverse(model))) * Normal;
	TexCoords = vertTexCoords;  
}