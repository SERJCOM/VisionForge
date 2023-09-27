#version 430 core

out vec4 FragColor;
  
in vec3 colorOut;
in vec3 NormalOut;
in vec3 PosFrag;
in vec2 TexCoords;
in vec4 fragPosLight;

struct LIGHT{
	float ambient;
	float specular;
	vec3 pos;
	vec3 color;
};


uniform LIGHT point_light[16];
uniform int len_point = 0;


uniform vec3 cameraPos;

uniform bool bool_texture_diffuse;
uniform sampler2D texture_diffuse;

uniform bool bool_texture_normal;
uniform sampler2D texture_normal;

uniform bool bool_texture_metalic;
uniform sampler2D texture_metalic;

uniform bool bool_texture_specular;
uniform sampler2D texture_specular;

uniform bool bool_texture_roughness;
uniform sampler2D texture_roughness;

uniform bool bool_texture_ao;
uniform sampler2D texture_ao;

uniform sampler2D shadowMap;

//========== P B R =================
uniform samplerCube irradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D brdfLUT;

struct sLightComponent{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// данные материала для PBR
vec3 albedo = vec3(0.5, 0.5, 0.5);
float metallic = 0.0;
float roughness = 1.0;
float ao = 1.0;
vec3 normalMap;


//расчет направленного света и приведения к трем составляющим света
sLightComponent CalcDirLight(LIGHT light, vec3 normal, vec3 viewDir, vec3 color);


// модель освещения кука-торренса
float CookTorrance(vec3 _normal, vec3 _light, vec3 _view, float roughness_val);


// расчет ортогональной тени
float CalcShadow(vec4 fragPosLight);

const float PI = 3.14159265359;
  
float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySchlickGGX(float NdotV, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);
vec3 fresnelSchlick(float cosTheta, vec3 F0);
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness);

vec3 getNormalFromMap();

void main()
{
	vec3 normal = normalize(NormalOut);
	vec3 camDir = normalize(cameraPos - PosFrag); // направление камеры
	vec3 R = reflect(-camDir, normal);

	

	if(bool_texture_diffuse) albedo = pow(texture(texture_diffuse, TexCoords).rgb, vec3(2.2));
	if(bool_texture_metalic) metallic = texture(texture_metalic, TexCoords).r;
	if(bool_texture_normal) {
		normalMap = getNormalFromMap();
		normal = normalMap;
	}
	if(bool_texture_roughness) roughness = texture(texture_roughness, TexCoords).r;
	if(bool_texture_ao) ao = texture(texture_ao, TexCoords).r;


	vec3 N = normal;
	vec3 V  = camDir;


	vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);
	            
    // Уравнение отражения
    vec3 Lo = vec3(0.0);

	// vec3 L = normalize(vec3(point_light[i].x_pos, point_light[i].y_pos, point_light[i].z_pos) - PosFrag);
	// vec3 H = normalize(camDir + L);
	// float distance = length(vec3(point_light[i].x_pos, point_light[i].y_pos, point_light[i].z_pos) - PosFrag);
	// float attenuation = 1.0 / (distance * distance);
	// vec3 radiance = vec3(vec3(point_light[i].x, point_light[i].y, point_light[i].z)) * attenuation;  



	vec3 ppos[16];
	// ppos[0] = point_light[0].pos;
	// ppos[1] = point_light[1].pos;
	// ppos[2] = point_light[2].pos;

	uint j = 0;
	for(int i = 0; i < 6; i++){
		ppos[i] = point_light[i].pos;
	}


	for(int i = 0; i < len_point; i++){

	// vec3 L = normalize(vec3(point_light[i].x_pos, point_light[i].y_pos, point_light[i].z_pos) - PosFrag);
	// vec3 H = normalize(camDir + L);
	// float distance = length(vec3(point_light[i].x_pos, point_light[i].y_pos, point_light[i].z_pos) - PosFrag);
	// float attenuation = 1.0 / (distance * distance);
	// vec3 radiance = vec3(vec3(point_light[i].x, point_light[i].y, point_light[i].z)) * attenuation;       

		
		vec3 L = normalize(ppos[i] - PosFrag);
		vec3 H = normalize(camDir + L);
		float distance = length(ppos[i] - PosFrag);
		float attenuation = 1.0 / (distance * distance);
		vec3 radiance = vec3(1000, 1000, 1000) * attenuation;      

		// vec3 L = normalize(vec3(15.0, 0, 0) - PosFrag);
		// vec3 H = normalize(camDir + L);
		// float distance = length(vec3(15.0, 0, 0) - PosFrag);
		// float attenuation = 1.0 / (distance * distance);
		// vec3 radiance = vec3(1000, 1000, 1000) * attenuation;        
		
		// BRDF Кука-Торренса
		float NDF = DistributionGGX(normal, H, roughness);        
		float G = GeometrySmith(normal, camDir, L, roughness);      
		vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);        

		vec3 nominator = NDF * G * F;
		float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001;
		vec3 specular = nominator / denominator;

		vec3 kS = F;
		vec3 kD = 1.0 - kS;
		kD *= 1.0 - metallic;	 

		float NdotL = max(dot(normal, L), 0.0);                
		Lo += (kD * albedo / PI + specular) * radiance * NdotL; 

	}

	//======================= 

	vec3 F = fresnelSchlickRoughness(max(dot(normal, camDir), 0.0), F0, roughness);

	vec3 kS = F;
	vec3 kD = 1.0 - kS;
	kD *= 1.0 - metallic;	


	vec3 irradiance = texture(irradianceMap, normal).rgb;
	vec3 diffuse = irradiance * albedo;

	const float MAX_REFLECTION_LOD = 4.0;
    vec3 prefilteredColor = textureLod(prefilterMap, R,  roughness * MAX_REFLECTION_LOD).rgb;    
    vec2 brdf = texture(brdfLUT, vec2(max(dot(N, V), 0.0), roughness)).rg;
    vec3 specular = prefilteredColor * (F * brdf.x + brdf.y);
	

	vec3 ambient = (kD * diffuse + specular) * ao;
	

    vec3 color = ambient + Lo ;
	
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));  

	// color = vec3(point_light[2].x_pos, point_light[2].y_pos, point_light[2].z_pos);

	FragColor = vec4(color, 1.0);

	//FragColor = vec4(0.3, 0.7, 0.2, 1.0);
}


//=========================================================================
//=========================================================================

sLightComponent CalcDirLight(LIGHT light, vec3 normal, vec3 viewDir, vec3 color){	
	vec3 lightDir = light.pos;
	lightDir = normalize(lightDir);
	
	float diff = max(dot(normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

	vec3 lightColor = light.color;
	
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

vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture(texture_normal, TexCoords).rgb * 2.0 - 1.0;


    vec3 Q1  = dFdx(PosFrag);
    vec3 Q2  = dFdy(PosFrag);
    vec2 st1 = dFdx(TexCoords);
    vec2 st2 = dFdy(TexCoords);

    vec3 N   = normalize(NormalOut);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}