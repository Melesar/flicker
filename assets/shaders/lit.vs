#version 420 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

layout (std140, binding=0) uniform Matrices
{
	mat4 viewProjectionMatrix;
};

uniform mat4 modelMatrix;

out vec2 texCoord0;
out vec3 outNormal;

void main()
{
    texCoord0 = texCoord;
	texCoord0.y = 1 - texCoord0.y;
	outNormal = normal;
	vec4 pos = viewProjectionMatrix * modelMatrix * vec4(position, 1);
	gl_Position = pos;
}