#version 420 core
out vec4 FragColor;
  
in vec2 outTexCoords;

 
uniform sampler2D screenTexture;
uniform sampler2D godRaysSampler;
uniform sampler2D bloomBlur;

 
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

uniform vec3 sunPos;

const float exposure = 0.3;
const float decay = 0.96;
const float density  = 0.95;
const float weight  = 0.5;
 
void main()
{ 
	vec3 FragPos = texture(gPosition, outTexCoords).rgb;
    vec3 Normal = texture(gNormal, outTexCoords).rgb;
    vec3 Albedo = texture(gAlbedoSpec, outTexCoords).rgb;
    float Specular = texture(gAlbedoSpec, outTexCoords).a;

    int NUM_SAMPLES = 80;
	vec2 tc = outTexCoords;
	vec2 deltatexCoord = (tc - (sunPos.xy*0.5 + 0.5));
	deltatexCoord *= 1.0/ float(NUM_SAMPLES);
	float illuminationDecay = 1.0f;

	vec4 godRayColor = texture(godRaysSampler , tc) * 0.4;
	for(int i = 0 ; i< NUM_SAMPLES ; i++)
	{
		tc-= deltatexCoord;
		vec4 samp = texture(godRaysSampler , tc )* vec4(1, 0.894, 0.517, 1.0);
		samp *= illuminationDecay*weight;
		godRayColor += samp;
		illuminationDecay *= decay;
	}

    vec4 realColor = vec4(Albedo, 1.0);

    realColor = ((vec4((vec3(godRayColor) * exposure), 1)) + (realColor*(1.0)));

	vec4 bloomColor = vec4(texture(bloomBlur, outTexCoords).rgb, 1);

	realColor += bloomColor;

	// realColor = realColor / (realColor + vec4(1.0));
	realColor = pow(realColor, vec4(1.0 / 2.2));
	FragColor = realColor;

	// FragColor= realColor;
}