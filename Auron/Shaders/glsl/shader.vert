#version 330 core

layout (location = 0) in vec3 aVertex;
layout (location = 1) in vec3 aColor;

out vec4 vSmoothColor;
uniform mat4 uMVP;
uniform float uTime;

void main() 
{ 
    vSmoothColor = vec4(aColor,1);
    gl_Position = uMVP*vec4(
        aVertex.x + sin(uTime) / 2,
        aVertex.y + cos(uTime) / 2,
        aVertex.z,
        1);
}