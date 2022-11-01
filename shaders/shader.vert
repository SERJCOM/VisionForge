#version 430 core
#extension GL_ARB_shader_storage_buffer_object : require

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 vertTexCoords;


struct LightStruct{
	// type:
	// 0: direction light
	// 1: point light
	// 2: projector
	int type;
	float ambient;
	float specular;
	
	float x_pos; // position of the light
	float y_pos;
	float z_pos;
	
	float x; // color of the light
	float y;
	float z;	
};

layout(std430, binding = 0) buffer ssboData
{
	LightStruct light[16];
};

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;
uniform int NUMBER_LIGHT;

struct DIRECTION_LIGHT{
	float ambient;
	float specular;
	float x_pos; // direction of the light
	float y_pos;
	float z_pos;
	
	float x; // color of the light
	float y;
	float z;	
};

out DIRECTION_LIGHT direction_light;

//out POINT_LIGHT{
	
//} point_light[16];


//out PROJECTOR{
	
//} projector[16];

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

	//colorOut = vec3(light[0].x, light[0].y, light[0].z);

	//lighting
	int len_point = 0, len_proj = 0;
	
	// for(int i = 0; i < NUMBER_LIGHT; i++){
	// 	int type = light[i].type;
		
	// 	if(type == 0){
	// 		direction_light.ambient = light[i].ambient;
	// 		direction_light.specular = light[i].specular;
			
	// 		direction_light.x = light[i].x;
	// 		direction_light.y = light[i].y;
	// 		direction_light.z = light[i].z;
			
	// 		direction_light.x_pos = light[i].x_pos;
	// 		direction_light.y_pos = light[i].y_pos;
	// 		direction_light.z_pos = light[i].z_pos;
	// 	}
	// }
}