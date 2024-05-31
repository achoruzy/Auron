// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "Source/Core/Shader.h"
#include <vector>
#include <glm/glm.hpp>

namespace Auron { 

    struct Vert {
        glm::vec3 position;
        glm::vec3 color;
    };

    class SceneObject
    {
    private:
        Vert vertices[4];
        std::vector<unsigned int> indices;
        Shader* material;
    public:
        SceneObject();
        ~SceneObject();
        Vert* GetVertices(unsigned int& count);
        std::vector<unsigned int>* GetIndices(unsigned int& count);
        Shader* GetMaterial();
    };
}