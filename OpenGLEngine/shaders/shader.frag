#version 330 core
out vec4 gl_FragColor;
  
in vec3 colorOut;
in vec3 NormalOut;
in vec3 PosFrag;

vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

uniform vec3 lightPos;
uniform vec3 cameraPos;

float specularStrength = 0.5;


vec3 norm = normalize(NormalOut);
vec3 lightDir = normalize(lightPos - PosFrag);  

vec3 diffuse  = max(dot(norm, lightDir), 0.0) * colorOut;


vec3 viewDir = normalize(cameraPos - PosFrag);
vec3 reflectDir = reflect(-lightDir, norm);  

float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
vec3 specular = specularStrength * spec * lightColor;  

void main()
{
   
    vec3 background = vec3(colorOut * lightColor * 0.3);
    vec3 result = vec3((background + diffuse + specular) * colorOut);
    gl_FragColor = vec4(result, 1.0);
}