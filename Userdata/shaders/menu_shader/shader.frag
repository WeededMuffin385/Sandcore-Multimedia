#version 330 core
out vec4 FragColor;

in vec2 fTexPos;

uniform sampler2D fTex;

void main()
{
    FragColor = texture(fTex, fTexPos) * vec4(1.0f,1.0f,1.0f,1.0f);
}