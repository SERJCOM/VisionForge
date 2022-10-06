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
	vec3 normal = normalize(NormalOut);
	
	vec3 color = texture(texture_diffuse1, TexCoords).rgb; // texture

	sLightComponent lightComp = CalcDirLight(direction_light, normal, cameraPos, color);
	
	float shadow = CalcShadow(fragPosLight); // calculating the shadow
	vec3 lighting = (lightComp.ambient  + (1.0 - shadow) * lightComp.diffuse ) * color; // calculating the final color of the fragment

	vec3 result = lighting;

	
	//float gamma = 2.2;
    //FragColor.rgb = pow(result.rgb, vec3(1.0/gamma)); // gamma correction

	FragColor = vec4(result, 1.0);
}

