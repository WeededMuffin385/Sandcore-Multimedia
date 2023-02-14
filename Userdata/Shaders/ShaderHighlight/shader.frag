#version 330 core
out vec4 fragColor;

in vec4 fColor;

void main()
{
	fragColor = fColor;
}