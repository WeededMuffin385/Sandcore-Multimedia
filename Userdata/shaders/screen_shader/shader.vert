#version 330 core
layout (location = 0) in float index;

out vec2 TexCoords;

vec2 frameCoords[6] = vec2[6](
    vec2(-1.0f,  1.0f),
    vec2(-1.0f, -1.0f),
    vec2( 1.0f, -1.0f),

    vec2(-1.0f,  1.0f),
    vec2( 1.0f, -1.0f),
    vec2( 1.0f,  1.0f)
);

vec2 texCoords[6] = vec2[6](
    vec2(0.0f, 1.0f),
    vec2(0.0f, 0.0f),
    vec2(1.0f, 0.0f),

    vec2(0.0f, 1.0f),
    vec2(1.0f, 0.0f),
    vec2(1.0f, 1.0f)
);


void main()
{
    gl_Position = vec4(frameCoords[int(index)].x, frameCoords[int(index)].y, 0.0, 1.0);
    TexCoords = texCoords[int(index)];
}