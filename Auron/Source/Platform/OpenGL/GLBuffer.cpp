// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "GLBuffer.h"
#include "Source/Core/Shader.h"
#include "Source/Core/Scene/SceneObject.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Auron {
    GLBuffer::GLBuffer(SceneObject* object, Shader* shader): object{object}, shader{shader}
    {
        Initialize();
    }

    GLBuffer::~GLBuffer()
    {
    }

    void GLBuffer::Initialize()
    {
        SetOrGenerateBuffers();

        // TODO rework for multi model per material
        Vert* vertices = object->GetVertices();
        std::vector<unsigned int>* indices = object->GetIndices();

        glBufferData(GL_ARRAY_BUFFER, 4*sizeof(Vert), vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size()*sizeof(int), indices->data(), GL_STATIC_DRAW);

        GLsizei stride = sizeof(Vert);

        // Base engine attributes
        glEnableVertexAttribArray((*shader)["vVertex"]);
        glVertexAttribPointer((*shader)["vVertex"], 3, GL_FLOAT, GL_FALSE, stride, (void*)0); // vertex data
        glEnableVertexAttribArray((*shader)["vColor"]);
        glVertexAttribPointer((*shader)["vColor"], 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offsetof(Vert, color));
    
        // TODO: Get MVP camera data out of here
        glm::mat4 P = glm::ortho(-1,1,-1,1);
        glm::mat4 MV = glm::mat4(1);
        float time = glfwGetTime();
        
        // Base engine uniforms
        shader->Use();
            shader->SetUniformMat4("uMVP", P*MV);
            shader->SetUniformFloat("uTime", time);
        shader->StopUsing();
    }

    void GLBuffer::DrawObject()
    {
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //  TODO: has to be parametrical
    }

    void GLBuffer::SetOrGenerateBuffers()
    {
        GLuint* vbo = &VBOs[shader];
        if (!(*vbo)) 
        {
            glGenBuffers(1, vbo);
            VBOs[shader] = *vbo;
        }
        
        GLuint* vao = &VAOs[shader];
        if (!(*vao)) 
        {
            glGenVertexArrays(1, vao);
            VAOs[shader] = *vao;
        }

        GLuint* ebo = &EBOs[shader];
        if (!(*ebo)) 
        {
            glGenBuffers(1, ebo);
            EBOs[shader] = *ebo;
        }

        glBindBuffer(GL_ARRAY_BUFFER, *vbo);
        glBindVertexArray(*vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    }
}