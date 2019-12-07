#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 transform;

out vec2 texCoord0;

void main()
{
    texCoord0 = texCoord;
	texCoord0.y = 1 - texCoord0.y;
	vec4 pos = transform * vec4(position, 1);
	gl_Position = pos;
}