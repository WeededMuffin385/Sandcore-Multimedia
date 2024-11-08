#version 330 core
layout (location = 0) in vec2 vPos;
layout (location = 1) in vec3 vColor;

out vec4 fColor;

void main()
{
    fColor = vec4(vColor, 1.0);
    gl_Position = vec4(vPos.xy, 0.0 , 1.0);
}