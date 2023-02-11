#version 330 core
out vec4 fragColor;

in vec4 fColor;
in vec3 fTexPos;

uniform sampler2DArray textureArray;

void main()
{
	fragColor = fColor * texture(textureArray, fTexPos);
}