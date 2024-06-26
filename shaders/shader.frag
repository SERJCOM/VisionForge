#version 430 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 SunColor;
layout (location = 2) out vec4 BrightColor;

layout (location = 3) out vec4 gPosition;
layout (location = 4) out vec4 gNormal;
layout (location = 5) out vec4 gAlbedoSpec;



in vec3 colorOut;
in vec3 NormalOut;
in vec3 PosFrag;
in vec2 TexCoords;
in vec4 fragPosLight;

struct LIGHT
{
	vec3 pos;
	vec3 color;
	vec3 brightness;
};

struct LIGHT_POINT_SHADOW
{
	vec3 pos;
	samplerCube depthmap;
	float far_plane;
};

const float PI = 3.14159265359;
const int SHADOW_MAX = 8;

uniform LIGHT point_light[16];
uniform int len_point = 0;

uniform LIGHT_POINT_SHADOW point_light_shadow[1];
uniform int len_point_light_shadow = 0;


uniform vec3 cameraPos;

uniform int mode_render = 0; // мод для рендеринга 

uniform int diffuse_mode;
uniform vec3 diffuse_u;
uniform bool bool_texture_diffuse;
uniform sampler2D texture_diffuse; // 0


uniform bool bool_texture_normal;
uniform sampler2D texture_normal; // 1

uniform float metallic_u;
uniform bool bool_texture_metalic;
uniform sampler2D texture_metalic; // 2

uniform bool bool_texture_specular;
uniform sampler2D texture_specular; // 3

uniform float roughness_u;
uniform bool bool_texture_roughness;
uniform sampler2D texture_roughness; // 4

uniform float ao_u;
uniform bool bool_texture_ao;
uniform sampler2D texture_ao; // 5

uniform sampler2D shadowMap; // 6
// uniform samplerCube depthMap; // для всенаправленных теней  // 0

//========== P B R =================
uniform samplerCube irradianceMap; // 1
uniform samplerCube prefilterMap;  // 2
uniform sampler2D brdfLUT;		   // 7

// данные материала для PBR
vec3 albedo = vec3(0.9, 0.9, 0.9);
float metallic = 0.0;
float roughness = 1.0;
float ao = 0.1;


// расчет ортогональной тени
float CalcShadow(vec4 fragPosLight);

// расчет всенаправленных теней
float CubeShadowCalculation(vec3 fragPos, vec3 lightPos, int index);

vec3 getNormalFromMap();

float DistributionGGX(vec3 normal, vec3 H, float roughness);
float GeometrySchlickGGX(float NdotV, float roughness);
float GeometrySmith(vec3 normal, vec3 camDir, vec3 L, float roughness);
vec3 fresnelSchlick(float cosTheta, vec3 F0);
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness);
float CookTorrance(vec3 _normal, vec3 _light, vec3 _view, float roughness_val);

void main()
{

	if (mode_render == 1)
	{
		SunColor = vec4(0.0, 0.0, 0.0, 1.0);
	}
	else if (mode_render == 2)
	{
		SunColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
	

	vec3 normal;

	if (bool_texture_diffuse)
		albedo = pow(texture(texture_diffuse, TexCoords).rgb, vec3(2.2));
	if (bool_texture_metalic)
		metallic = texture(texture_metalic, TexCoords).r;
	if (bool_texture_normal)
	{
		normal = getNormalFromMap();
	}
	else
	{
		normal = normalize(NormalOut);
	}

	if (bool_texture_roughness)
		roughness = texture(texture_roughness, TexCoords).r;
	if (bool_texture_ao)
		ao = texture(texture_ao, TexCoords).r;

	vec3 camDir = normalize(cameraPos - PosFrag); // направление камеры
	vec3 reflection = reflect(-camDir, normal);

	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);

	// Уравнение отражения
	vec3 Lo = vec3(0.0);

	// debug
	// vec3 shadow_pos_d = vec3(-24, 2, -19);
	// vec3 brightness = vec3(1, 1, 1);

	// LIGHT test_light[1];
	// test_light[0].color = vec3(1, 1, 0);
	// test_light[0].pos = vec3(10, 10, 10);
	// test_light[0].brightness = vec3(100, 100, 100);
	

	for (int i = 0; i < len_point; i++)
	{

		vec3 L = normalize(point_light[i].pos - PosFrag);
		vec3 H = normalize(camDir + L + vec3(0.1, 0.1, 0.1));
		float distance = length(point_light[i].pos - PosFrag) + 0.001;
		float attenuation = 1.0 / (distance * distance + 0.001);
		vec3 radiance = point_light[i].color * attenuation * point_light[i].brightness;

		float NDF = DistributionGGX(normal, H, roughness);
		float G = GeometrySmith(normal, camDir, L, roughness);
		vec3 F = fresnelSchlick(max(dot(H, camDir), 0.0), F0);

		vec3 nominator = NDF * G * F;
		float denominator = 4 * max(dot(normal, camDir), 0.0) * max(dot(normal, L), 0.0) + 0.001;
		vec3 specular = nominator / denominator;

		vec3 kS = F;
		vec3 kD = 1.0 - kS;
		kD *= 1.0 - metallic;

		float NdotL = max(dot(normal, L), 0.0);
		Lo += (kD * albedo / PI + specular) * (radiance) * NdotL;
	}

	vec3 shadow_color = vec3(0, 0, 0);
	for (int i = 0; i < len_point_light_shadow; i++)
	{
		float shadow = CubeShadowCalculation(PosFrag, point_light_shadow[i].pos, i);
		shadow_color += (1 - shadow);
	}

	//=======================

	vec3 F = fresnelSchlickRoughness(max(dot(normal, camDir), 0.0), F0, roughness);

	vec3 kS = F;
	vec3 kD = 1.0 - kS;
	kD *= 1.0 - metallic;

	vec3 irradiance = texture(irradianceMap, normal).rgb;
	vec3 diffuse = irradiance * albedo;

	const float MAX_REFLECTION_LOD = 4.0;
	vec3 prefilteredColor = textureLod(prefilterMap, reflection, roughness * MAX_REFLECTION_LOD).rgb;
	vec2 brdf = texture(brdfLUT, vec2(max(dot(normal, camDir), 0.0), roughness)).rg;
	vec3 specular = prefilteredColor * (F * brdf.x + brdf.y);

	vec3 ambient =  (kD * diffuse + specular) * ao ;

	vec3 color = ambient + Lo ;

	FragColor = vec4(color, 1.0);

	// if (any(isnan(FragColor))) FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);


    if(dot(color, vec3(0.1, 0.1, 0.1)) > 1.0)
        BrightColor = vec4(color, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);

	gPosition = vec4(PosFrag, 0.0);
	gNormal = vec4(normal, 0.0);
	gAlbedoSpec.rgb = FragColor.rgb;
	gAlbedoSpec.a = specular.r;
}

//=========================================================================
//=========================================================================

float CookTorrance(vec3 _normal, vec3 _light, vec3 _view, float roughness_val)
{
	if (roughness_val <= 0.0)
		return 0.0;

	vec3 half_vec = normalize(_view + _light);
	float NdotL = max(dot(_normal, _light), 0.0);
	float NdotV = max(dot(_normal, _view), 0.0);
	float NdotH = max(dot(_normal, half_vec), 1.0e-7);
	float VdotH = max(dot(_view, half_vec), 0.0);

	float geometric = 2.0 * NdotH / VdotH;
	geometric = min(1.0, geometric * min(NdotV, NdotL));

	float r_sq = roughness_val * roughness_val;
	float NdotH_sq = NdotH * NdotH;
	float NdotH_sq_r = 1.0 / (NdotH_sq * r_sq);
	float roughness_exp = (NdotH_sq - 1.0) * (NdotH_sq_r);
	float roughness = exp(roughness_exp) * NdotH_sq_r / (4.0 * NdotH_sq);

	float fresnel = 1.0 / (1.0 + NdotV);

	float Rs = min(1.0, (fresnel * geometric * roughness) / (NdotV * NdotL + 1.0e-7));

	return Rs;
}

float CalcShadow(vec4 fragPosLight)
{
	vec3 projCoords = fragPosLight.xyz / fragPosLight.w;
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;
	float shadow = currentDepth - 0.005 > closestDepth ? 1.0 : 0.0;
	return shadow;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
	return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float DistributionGGX(vec3 normal, vec3 H, float roughness)
{
	float a = roughness * roughness;
	float a2 = a * a;
	float NdotH = max(dot(normal, H), 0.0);
	float NdotH2 = NdotH * NdotH;

	float num = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;

	return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
	float r = (roughness + 1.0);
	float k = (r * r) / 8.0;

	float num = NdotV;
	float denom = NdotV * (1.0 - k) + k;

	return num / denom;
}
float GeometrySmith(vec3 normal, vec3 camDir, vec3 L, float roughness)
{
	float NdotV = max(dot(normal, camDir), 0.0);
	float NdotL = max(dot(normal, L), 0.0);
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

	vec3 Q1 = dFdx(PosFrag);
	vec3 Q2 = dFdy(PosFrag);
	vec2 st1 = dFdx(TexCoords);
	vec2 st2 = dFdy(TexCoords);

	vec3 normal = normalize(NormalOut);
	vec3 T = normalize(Q1 * st2.t - Q2 * st1.t);
	vec3 B = -normalize(cross(normal, T));
	mat3 TBN = mat3(T, B, normal);

	return normalize(TBN * tangentNormal);
}

float CubeShadowCalculation(vec3 fragPos, vec3 lightPos, int index)
{
	vec3 fragToLight = fragPos - lightPos;

	float closestDepth = texture(point_light_shadow[index].depthmap, fragToLight).r;

	closestDepth *= point_light_shadow[index].far_plane;

	float currentDepth = length(fragToLight);

	float bias = 1.0;
	float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

	return shadow;
}