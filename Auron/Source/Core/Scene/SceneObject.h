// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "Source/Core/Shader.h"
#include <vector>

namespace Auron { 
    class SceneObject
    {
    private:
        std::vector<float> m_vertices;
        std::vector<unsigned int> m_indices;
        Shader* m_material;
    public:
        SceneObject();
        ~SceneObject();
        std::vector<float>* GetVertices();
        std::vector<unsigned int>* GetIndices();
        Shader* GetMaterial();
    };
}