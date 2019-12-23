#version 420 core

in vec2 texCoord0;
in vec3 Normal;
in vec3 FragPos;

struct Material
{
    sampler2D diffuseTex;
    sampler2D specularTex;
    vec4 diffuseColor;
    vec4 specularColor;
    float shininess;
};

uniform Material material;

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
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(lightDir, norm), 0.0);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);

    vec3 diffuseTextureSample = vec3(texture(material.diffuseTex, texCoord0));
    vec3 lAmbient = light.ambient * diffuseTextureSample;
    vec3 lDiffuse = light.diffuse * diff * diffuseTextureSample * vec3(material.diffuseColor);
    vec3 lSpecular = light.specular * spec * vec3(texture(material.specularTex, texCoord0)) * vec3(material.specularColor);

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadrant * distance * distance);

    return 4 * attenuation * (lAmbient + lDiffuse + lSpecular);
}

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(cameraPos - FragPos);

    vec3 resultColor = vec3(0);
    for(int i = 0; i < 1; i++)
    {
        resultColor += calcPointLight(pointLights[i], norm, viewDir);
    }

    FragColor = vec4(resultColor, 1);
} 