#version 330 core

layout (location = 0) in vec3 vVertex;
layout (location = 1) in vec3 vColor;

out vec4 vSmoothColor;
// uniform mat4 MVP;

void main() 
{ 
    vSmoothColor = vec4(0.0, 1.0, 1.0, 1.0);
    gl_Position = vec4(vVertex.x, vVertex.y, vVertex.z, 1.0); 
}