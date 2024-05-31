#version 330 core

layout (location = 0) out vec4 vFragColor;

in vec4 vSmoothColor;
uniform float uTime;

void main() 
{
    vec4 Color = vec4(vSmoothColor.x * sin(uTime) * 4, 
        vSmoothColor.y * cos(uTime) * 6, 
        vSmoothColor.z, 
        vSmoothColor.w);
    vFragColor = Color;
}