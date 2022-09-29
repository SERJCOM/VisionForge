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






float CalcShadow(vec4 fragPosLight){
	vec3 projCoords = fragPosLight.xyz / fragPosLight.w;
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;
	float shadow = currentDepth - 0.005> closestDepth ? 1.0 : 0.0;
	//float shadow = closestDepth  ;
	return shadow;
}


void main()
{

	vec3 t = texture(texture_diffuse1, TexCoords).rgb;
	
	//vec3 t = vec3(0.5, 0.3, 0.2);
	
	float shadow = CalcShadow(fragPosLight);
	vec3 lighting = (0.15 * t + (1 - shadow)) * t;

	FragColor = vec4(lighting, 1.0);	
	
	
	//FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
	

}

