#version 430 core

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


// модель освещения кука-торренса
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
	vec3 lighting = (0.75 * t  + (1 - shadow)) * t;

	vec4 result = vec4(lighting, 1.0);	
	
	float gamma = 2.2;
    //FragColor.rgb = pow(result.rgb, vec3(1.0/gamma));
	FragColor.rgb = colorOut;
}

