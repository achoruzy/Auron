#version 330 core

layout (location = 0) out vec4 vFragColor;

in vec4 vSmoothColor;

void main() 
{ 
    vFragColor = vec4(0.1f, 0.5f, 0.7f, 1.0f);
}