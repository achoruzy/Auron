// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "GLBuffer.h"
#include "GLSLShader.h"
#include "Source/Core/Shader.h"
#include "Source/Core/Scene/SceneObject.h"
#include "Source/Core/Logger.h"
#include <GLFW/glfw3.h>


namespace Auron {
    GLBuffer::GLBuffer(SceneObject* object, Shader* shader): object{object}, shader{shader}
    {
        Initialize();
    }

    GLBuffer::~GLBuffer()
    {
        // glDeleteBuffers(1, &EBO);
        // glDeleteBuffers(1, &VAO);
        // glDeleteBuffers(1, &VBO);
    }

    void GLBuffer::Initialize()
    {
        GenerateBuffers();

        vertices = object->GetVertices(vertices_count);
        indices = object->GetIndices(indices_count);
    }

    void GLBuffer::DrawObject()
    {
        GLsizei stride = sizeof(Vert);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        // Base engine attributes
        glVertexAttribPointer((*shader)["aVertex"], 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
        SetAttributeEnabled("aVertex");
        glVertexAttribPointer((*shader)["aColor"], 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offsetof(Vert, color));
        SetAttributeEnabled("aColor");

        glBufferData(GL_ARRAY_BUFFER, 4*sizeof(Vert), vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_count*sizeof(int), indices->data(), GL_STATIC_DRAW);
        
        glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0);
    }

    void GLBuffer::GenerateBuffers()
    {
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &EBO);

        if (!VBO || !VAO || !EBO)
        {
            LOG_ERROR("Object buffer couldn't be initialized.");
            return;
        }
    }
    
    void GLBuffer::SetAttributeEnabled(const std::string& attribute)
    {
        if (shader->HasAttribute(attribute)) glEnableVertexAttribArray((*shader)[attribute]);
        else glDisableVertexAttribArray((*shader)[attribute]);
    }
}