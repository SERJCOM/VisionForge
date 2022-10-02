#version 430 core
#extension GL_ARB_shader_storage_buffer_object : require

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 vertTexCoords;

struct LightStruct{
	float ambient;
	float specular;
	vec3 color;
};

layout(std430, binding = 0) buffer ssboData
{
	LightStruct light[16];
};

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

uniform bool texturePermit;
uniform vec3 lightColor;


out vec3 colorOut;
out vec3 NormalOut;
out vec3 PosFrag;
out vec2 TexCoords;
out vec4 fragPosLight;

 
void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0);
    PosFrag = vec3(model * vec4(pos, 1.0));
    //colorOut = vec3(lightColor);
	colorOut = light[0].color;
	
    NormalOut = mat3(transpose(inverse(model))) * Normal;;
	TexCoords = vertTexCoords;    
	
    fragPosLight = lightSpaceMatrix * vec4(PosFrag, 1.0);
}