// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "SceneObject.h"
#include "Source/Platform/OpenGL/GLSLShader.h"

namespace Auron {
    SceneObject::SceneObject()
    {
        // TODO: -> component and stack
        m_vertices = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
        };
        m_indices = {
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };
        m_material = new GLSLShader();
        m_material->CreateProgram();
    }
    
    SceneObject::~SceneObject()
    {
        delete m_material;
    }

    std::vector<float>* SceneObject::GetVertices()
    {
        return &m_vertices;
    }

    std::vector<unsigned int>* SceneObject::GetIndices()
    {
        return &m_indices;
    }

    Shader* SceneObject::GetMaterial()
    {
        return m_material;
    }
}
