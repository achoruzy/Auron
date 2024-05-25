// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "SceneObject.h"
#include "Source/Platform/OpenGL/GLSLShader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Auron {

    SceneObject::SceneObject()
    {
        vertices[0].position = glm::vec3{0.5f,  0.5f, 0.0f};
        vertices[1].position = glm::vec3{0.5f, -0.5f, 0.0f};
        vertices[2].position = glm::vec3{-0.5f, -0.5f, 0.0f};
        vertices[3].position = glm::vec3{-0.5f,  0.5f, 0.0f};

        vertices[0].color = glm::vec3{0.5f, 0.0f, 1.0f};
        vertices[1].color = glm::vec3{0.5f, 0.5f, 1.0f};
        vertices[2].color = glm::vec3{1.0f, 0.0f, 0.0f};
        vertices[3].color = glm::vec3{0.0f,  1.0f, 0.0f};

        indices = {
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };

        std::string vertexShaderSourcePath = "Auron/Shaders/glsl/shader.vert";
        std::string fragmentShaderSourcePath = "Auron/Shaders/glsl/shader.frag";

        material = new GLSLShader();
        material->LoadFromFile(vertexShaderSourcePath, ShaderType::VERTEX);
        material->LoadFromFile(fragmentShaderSourcePath, ShaderType::FRAGMENT);
        material->CreateProgram();
        material->Use();
            material->AddAttribute("vVertex"); // rework to add data info with function somehow
            material->AddAttribute("vColor");
            material->AddUniform("MVP");
        material->StopUsing();
    }
    
    SceneObject::~SceneObject()
    {
        delete material;
    }

    Vert* SceneObject::GetVertices()
    {
        return vertices;
    }

    std::vector<unsigned int>* SceneObject::GetIndices()
    {
        return &indices;
    }

    Shader* SceneObject::GetMaterial()
    {
        return material;
    }
}
