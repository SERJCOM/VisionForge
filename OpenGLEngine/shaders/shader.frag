#version 330 core
out vec4 gl_FragColor;
  
in vec3 colorOut;
in vec3 NormalOut;
in vec3 PosFrag;

uniform vec3 cameraPos;

struct Light{
	vec3 lightColor; // цвет источника света
	vec3 lightPos;
	
	float constant;
    float linear;
    float quadratic;
	
	vec3 direction;
    float cutOff;
};

uniform	Light	LIGHT;
uniform	Light	FLASHLIGHT;

vec3 calcPointLight(Light light, vec3 normal, vec3 fragPos){
	float ambientStrength = 0.1; // коаф фона 
	vec3 ambient = ambientStrength * light.lightColor;
	vec3 lightDir = normalize(light.lightPos - PosFrag);  
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * light.lightColor;
	vec3 result = (ambient + diffuse) * vec3(1.0f, 0.0f, 0.5f);
	return result;
	
}

vec3 CalcDampingLight(Light light, vec3 FragPos, vec3 normal){
	float distance = length(light.lightPos - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	float ambientStrength = 0.1; // коаф фона 
	vec3 ambient = ambientStrength * light.lightColor;
	vec3 lightDir = normalize(light.lightPos - PosFrag);  
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * light.lightColor;
	
	ambient *= attenuation; 
	diffuse *= attenuation;

	vec3 result = (ambient + diffuse) * vec3(1.0f, 0.0f, 0.5f);
	return result;
	
}

vec3 CalcFlashLight(Light light, vec3 view, vec3 FragPos, vec3 normal){
	vec3 lightDir = normalize(light.lightPos - FragPos);
	float theta = dot(lightDir, normalize(-light.direction)); 
	
	if(theta > light.cutOff){
        float distance = length(light.lightPos - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	float ambientStrength = 0.1; // коаф фона 
	vec3 ambient = ambientStrength * light.lightColor;
	vec3 lightDir = normalize(light.lightPos - PosFrag);  
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * light.lightColor;
	
	ambient *= attenuation; 
	diffuse *= attenuation;

	vec3 result = (ambient + diffuse) * vec3(1.0f, 0.0f, 0.5f);
		return result;
	}
	return light.lightColor * 0.1;
}

void main()
{
	vec3 norm = normalize(NormalOut);
	vec3 viewDir = normalize(cameraPos - PosFrag);

	vec3 result = CalcDampingLight(LIGHT,PosFrag, norm);
	
	gl_FragColor = vec4(result, 1.0);
}

