#version 450 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in float vColor;

out vec4 fColor;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main(){
	gl_Position = proj * view * model * vec4(vPos, 1.0);
	fColor = vec4(vColor, 1.0);
}