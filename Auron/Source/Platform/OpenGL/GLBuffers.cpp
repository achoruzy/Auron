// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "GLBuffers.h"
#include "Source/Core/Shader.h"
#include "Source/Core/Scene/SceneObject.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Auron {
    GLBuffer::GLBuffer()
    {

    }

    GLBuffer::~GLBuffer()
    {
    }

    void GLBuffer::DrawObject(SceneObject* object)
    {
        // TODO rework for multi model per material
        SetOrGenerateBuffers(object->GetMaterial());



        auto vertices = object->GetVertices();
        auto indices = object->GetIndices();
        auto material = object->GetMaterial();
        glBufferData(GL_ARRAY_BUFFER, vertices->size()*sizeof(float), vertices->data(), GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size()*sizeof(int), indices->data(), GL_STATIC_DRAW);

        glVertexAttribPointer((*material)["vVertex"], 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0); // vertex data
        glEnableVertexAttribArray((*material)["vVertex"]);
        // =============================

        glm::mat4 P = glm::ortho(-1,1,-1,1);
        glm::mat4 MV = glm::mat4(1);
        // GLsizei stride = sizeof(Vert);


        // glEnableVertexAttribArray((*material)["vVertex"]);
        // glVertexAttribPointer((*material)["vVertex"], 3, GL_FLOAT, GL_FALSE, stride, 0);
        // glEnableVertexAttribArray((*material)["vColor"]);
        // glVertexAttribPointer((*material)["vColor"], 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offsetof(Vert, color));


        // TODO: get out settings for polygon drawing; may be GL_FILL/GL_LINE
        object->GetMaterial()->Use();
            glUniformMatrix4fv((*material)("MVP"), 1, GL_FALSE, glm::value_ptr(P*MV)); // needs to be in USE
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        object->GetMaterial()->StopUsing();
    }

    void GLBuffer::SetOrGenerateBuffers(Shader* shader)
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