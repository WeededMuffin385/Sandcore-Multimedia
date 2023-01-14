#version 330 core
layout (location = 0) in vec2 vPos;
layout (location = 1) in float vIndex;

out vec2 fTexPos;

vec2 texCoords[4] = vec2[4](
    vec2(0.0f, 1.0f),
    vec2(0.0f, 0.0f),
    vec2(1.0f, 0.0f),
    vec2(1.0f, 1.0f)
);


void main()
{
    gl_Position = vec4(vPos, 0.0, 1.0);
    fTexPos = texCoords[int(vIndex)];
}