#version 450 core
out vec4 fragColor;

in vec2 fTex;
uniform sampler2D texture0;

void main()
{
    fragColor = texture(texture0, fTex);
} 