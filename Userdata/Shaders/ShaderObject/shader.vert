#version 450 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTex;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec2 fTex;

void main()
{
	gl_Position = proj * view * model * vec4(vPos, 1.0);
	fTex = vTex;
}