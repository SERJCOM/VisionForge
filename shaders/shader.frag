#version 430 core

out vec4 FragColor;
  
in vec3 colorOut;
in vec3 NormalOut;
in vec3 PosFrag;
in vec2 TexCoords;
in vec4 fragPosLight;


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

in DIRECTION_LIGHT direction_light;


uniform vec3 cameraPos;
uniform sampler2D texture_diffuse1;
uniform sampler2D shadowMap;

struct sLightComponent{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// данные материала для PBR
vec3 albedo = vec3(0.0, 0.0, 1.0);
float metallic = 0.1;
float roughness = 1.0;
float ao = 0.4;


//расчет направленного света и приведения к трем составляющим света
sLightComponent CalcDirLight(DIRECTION_LIGHT light, vec3 normal, vec3 viewDir, vec3 color);


// модель освещения кука-торренса
float CookTorrance(vec3 _normal, vec3 _light, vec3 _view, float roughness_val);


// расчет ортогональной тени
float CalcShadow(vec4 fragPosLight);

const float PI = 3.14159265359;
  
float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySchlickGGX(float NdotV, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);
vec3 fresnelSchlick(float cosTheta, vec3 F0);


void main()
{
	vec3 normal = normalize(NormalOut);

	vec3 camDir = normalize(cameraPos - PosFrag); // направление камеры
	vec3 L = normalize(vec3(direction_light.x_pos, direction_light.y_pos, direction_light.z_pos) - PosFrag);
	vec3 H = normalize(camDir + L);
	float distance = length(vec3(direction_light.x_pos, direction_light.y_pos, direction_light.z_pos) - PosFrag);
	float attenuation = 1.0 / (distance * distance);
    vec3 radiance = vec3(direction_light.x, direction_light.y, direction_light.z) * attenuation;      

	vec3 F0  = vec3(0.04);
	//F0 = mix(F0, albedo, metallic);
	vec3 F = fresnelSchlick(max(dot(H, camDir), 0.0), F0);

	vec3 Lo = vec3(0.0);

	float NDF = DistributionGGX(normal, H, roughness);        
	float G = GeometrySmith(normal, camDir, L, roughness);            

	vec3 numerator = NDF * G * F;
	float denominator = 4.0 * max(dot(normal, camDir), 0.0) * max(dot(normal, L), 0.0);
	vec3 specular = numerator / max(denominator, 0.001);  

	vec3 kS = F;
	vec3 kD = vec3(1.0) - kS;
	kD *= 1.0 - metallic;	

	float NdotL = max(dot(normal, L), 0.0);                
	Lo += (kD * albedo / PI + specular) * radiance * NdotL; 

	vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient +  Lo;

	color = color / (color + vec3(1.0));
    
	// Гамма-коррекция
    color = pow(color, vec3(1.0/2.2)); 


	FragColor = vec4(color, 1.0);
	
	//vec3 color = texture(texture_diffuse1, TexCoords).rgb; // texture

	// sLightComponent lightComp = CalcDirLight(direction_light, normal, cameraPos, color);
	
	// float shadow = CalcShadow(fragPosLight); // calculating the shadow
	// vec3 lighting = (lightComp.ambient  + (1.0 - shadow) * lightComp.diffuse ) * color; // calculating the final color of the fragment

	//vec3 result = lighting;
	
	// float gamma = 2.2;
    // result = pow(result.rgb, vec3(1.0/gamma)); // gamma correction

	//FragColor = vec4(result, 1.0);
}





sLightComponent CalcDirLight(DIRECTION_LIGHT light, vec3 normal, vec3 viewDir, vec3 color){	
	vec3 lightDir = vec3(light.x_pos, light.y_pos, light.z_pos);
	lightDir = normalize(lightDir);
	
	float diff = max(dot(normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

	vec3 lightColor = vec3(light.x, light.y, light.z);
	
	vec3 ambient = light.ambient * color;
	vec3 diffuse = diff * lightColor;
    vec3 specular = vec3(light.specular);

	sLightComponent lightReturn;
	lightReturn.ambient = ambient;
	lightReturn.diffuse = diffuse;
	lightReturn.specular = specular;
	
	//return (ambient + diffuse + specular);
	return lightReturn;
}

float CookTorrance(vec3 _normal, vec3 _light, vec3 _view, float roughness_val){
	if (roughness_val <= 0.0) return 0.0;

	vec3  half_vec = normalize( _view + _light );
	float NdotL    = max( dot( _normal, _light ), 0.0 );
	float NdotV    = max( dot( _normal, _view ), 0.0 );
	float NdotH    = max( dot( _normal, half_vec ), 1.0e-7 );
	float VdotH    = max( dot( _view,   half_vec ), 0.0 );
	
	float geometric = 2.0 * NdotH / VdotH;
        geometric = min( 1.0, geometric * min(NdotV, NdotL) );
		
	float r_sq          = roughness_val * roughness_val;
    float NdotH_sq      = NdotH * NdotH;
    float NdotH_sq_r    = 1.0 / (NdotH_sq * r_sq);
    float roughness_exp = (NdotH_sq - 1.0) * ( NdotH_sq_r );
    float roughness     = exp(roughness_exp) * NdotH_sq_r / (4.0 * NdotH_sq );
	
	float fresnel       = 1.0 / (1.0 + NdotV);
	
	float Rs = min(1.0, (fresnel * geometric * roughness) / (NdotV * NdotL + 1.0e-7));
	
	return Rs;
}

float CalcShadow(vec4 fragPosLight){
	vec3 projCoords = fragPosLight.xyz / fragPosLight.w;
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;
	float shadow = currentDepth - 0.005> closestDepth ? 1.0 : 0.0;
	return shadow;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}  


float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}
 
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;
 
    float num = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}