#version 420 core
out vec4 FragColor;
  
in vec2 outTexCoords;

 
uniform sampler2D screenTexture;
uniform sampler2D godRaysSampler;

uniform vec3 sunPos;

const float exposure = 0.3;
const float decay = 0.96;
const float density  = 0.95;
const float weight  = 0.5;
 
void main()
{ 


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

    vec4 realColor = texture(screenTexture , outTexCoords);

    FragColor = ((vec4((vec3(godRayColor) * exposure), 1)) + (realColor*(1.0)));

    //  FragColor= realColor;
}