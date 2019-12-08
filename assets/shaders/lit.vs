#version 420 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

layout (std140, binding=0) uniform Camera
{
	mat4 viewProjectionMatrix;
	vec3 cameraPos;
};

uniform mat4 modelMatrix;

out vec2 texCoord0;
out vec3 Normal;
out vec3 FragPos;

void main()
{
    texCoord0 = aTexCoord;
	Normal = mat3(transpose(inverse(modelMatrix))) * aNormal;
	FragPos = vec3(modelMatrix * vec4(aPosition, 1));

	vec4 pos = viewProjectionMatrix * modelMatrix * vec4(aPosition, 1);
	gl_Position = pos;
}