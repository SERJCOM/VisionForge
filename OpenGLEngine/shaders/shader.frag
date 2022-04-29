#version 330 core
out vec4 gl_FragColor;
  
in vec3 colorOut;
in vec3 NormalOut;
in vec3 PosFrag;

uniform vec3 cameraPos;

struct PointLight{
	vec3 lightColor; // цвет источника света
	vec3 lightPos;
};

uniform PointLight POINTLIGHT;

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos){
	float ambientStrength = 0.1; // коаф фона 
	vec3 ambient = ambientStrength * light.lightColor;
	vec3 lightDir = normalize(light.lightPos - PosFrag);  
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * light.lightColor;
	vec3 result = (ambient + diffuse) * vec3(1.0f, 0.0f, 0.5f);
	return result;
	
}

void main()
{
	vec3 norm = normalize(NormalOut);
	vec3 viewDir = normalize(cameraPos - PosFrag);

	gl_FragColor = vec4(calcPointLight(POINTLIGHT, norm, PosFrag), 1.0);
}

