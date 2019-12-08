#version 330 core

in vec2 texCoord0;
in vec3 outNormal;

uniform sampler2D diffuse;
uniform vec4 color;

out vec4 FragColor;

void main()
{
    FragColor = color;
    // FragColor = texture(diffuse, texCoord0) * color;
} 