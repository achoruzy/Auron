// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "GLBuffers.h"
#include "Source/Core/Shader.h"
#include "Source/Core/Scene/SceneObject.h"
#include <GLFW/glfw3.h>

namespace Auron {
    GLBuffers::GLBuffers()
    {

    }

    GLBuffers::~GLBuffers()
    {
    }

    void GLBuffers::DrawObject(SceneObject* object)
    {
        // TODO rework for multi model per material
        auto vertices = object->GetVertices();
        auto indices = object->GetIndices();
        SetOrGenerateBuffers(object->GetMaterial());

        glBufferData(GL_ARRAY_BUFFER, vertices->size()*sizeof(float), vertices->data(), GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size()*sizeof(int), indices->data(), GL_STATIC_DRAW);

        // TODO: get out settings for polygon drawing; may be GL_FILL/GL_LINE
        object->GetMaterial()->Use();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void GLBuffers::SetOrGenerateBuffers(Shader* shader)
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