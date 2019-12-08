#version 420 core

in vec2 texCoord0;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D diffuse;
uniform vec4 color;

struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadrant;
};

#define NUM_POINT_LIGHTS 4

layout (std140, binding=0) uniform Camera
{
	mat4 viewProjectionMatrix;
	vec3 cameraPos;
};

layout (std140, binding=1) uniform Lights
{
    PointLight pointLights[NUM_POINT_LIGHTS];
};

out vec4 FragColor;

vec3 calcPointLight(PointLight light, vec3 norm, vec3 viewDir)
{
    int shininess = 32;
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(lightDir, norm), 0.0);
    vec3 reflectDir = reflect(lightDir, norm);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0), shininess);

    vec3 lAmbient = light.ambient * vec3(color);
    vec3 lDiffuse = light.diffuse * diff * vec3(color);
    vec3 lSpecular = light.specular * spec * vec3(color);

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadrant * distance * distance);

    return /*attenuation **/ vec3(lAmbient + lDiffuse + lSpecular);
}

void main()
{
    vec3 ligtPos = vec3(-1, 2, -3);

    int shininess = 32;
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(ligtPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    vec3 resultColor = vec3(0);
    for(int i = 0; i < NUM_POINT_LIGHTS; i++)
    {
        resultColor += calcPointLight(pointLights[i], norm, viewDir);
    }

    FragColor = vec4(resultColor, 1);
    // FragColor = (diff + spec) * color;
    // FragColor = texture(diffuse, texCoord0) * color;
} 