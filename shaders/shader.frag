#version 330 core
out vec4 FragColor;
  
in vec3 colorOut;
in vec3 NormalOut;
in vec3 PosFrag;
in vec2 TexCoords;
in vec4 fragPosLight;


uniform vec3 cameraPos;
uniform sampler2D texture_diffuse1;
uniform sampler2D shadowMap;
uniform vec3 lightPos;


// расчет ортогональной тени
float CalcShadow(vec4 fragPosLight){
	vec3 projCoords = fragPosLight.xyz / fragPosLight.w;
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;
	float shadow = currentDepth - 0.005> closestDepth ? 1.0 : 0.0;
	return shadow;
}


void main()
{

	vec3 t = texture(texture_diffuse1, TexCoords).rgb;
	
	float shadow = CalcShadow(fragPosLight);
	vec3 lighting = (0.15 * t + (1 - shadow)) * t;

	FragColor = vec4(lighting, 1.0);	
}

