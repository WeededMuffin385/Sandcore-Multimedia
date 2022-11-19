#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in float vShade;
layout (location = 2) in float vTexId;
layout (location = 3) in float vIndex;

out vec4 fColor;
out vec3 fTexPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float capacity;

vec2 texCoords[4] = vec2[4](
	vec2(0.0f, 0.0f),
	vec2(1.0f, 0.0f),
	vec2(1.0f, 1.0f),
	vec2(0.0f, 1.0f)
);

float actual_layer(float layer){
	return max(0, min(capacity - 1, floor(layer + 0.5)));
}

void main()
{
	gl_Position = projection * view * model * vec4(vPos, 1.0);
	fColor = vec4(vec3(1.0f, 1.0f, 1.0f) * vShade, 1.0);
	fTexPos = vec3(texCoords[int(vIndex)], actual_layer(vTexId));
}