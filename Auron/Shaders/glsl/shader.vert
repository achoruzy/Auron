#version 330 core

layout (location = 0) in vec3 vVertex;
layout (location = 1) in vec3 vColor;

out vec4 vSmoothColor;
uniform mat4 uMVP;
uniform float uTime;

void main() 
{ 
    vSmoothColor = vec4(vColor,1);
    gl_Position = uMVP*vec4(
        vVertex.x + sin(uTime) / 2,
        vVertex.y + cos(uTime) / 2,
        vVertex.z,
        1);
}