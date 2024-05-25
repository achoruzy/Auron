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
        vertices = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
        };

        // vertices[0].position = glm::vec3{0.5f,  0.5f, 0.0f};
        // vertices[1].position = glm::vec3{0.5f, -0.5f, 0.0f};
        // vertices[2].position = glm::vec3{-0.5f, -0.5f, 0.0f};
        // vertices[3].position = glm::vec3{-0.5f,  0.5f, 0.0f};

        // vertices[0].color = glm::vec3{0.5f, 0.0f, 1.0f};
        // vertices[1].color = glm::vec3{0.5f, 0.5f, 1.0f};
        // vertices[2].color = glm::vec3{1.0f, 0.0f, 0.0f};
        // vertices[3].color = glm::vec3{0.0f,  1.0f, 0.0f};

        indices = {
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };

        std::string vertexShaderSourcePath = "Auron/Shaders/glsl/shader.vert";
        std::string fragmentShaderSourcePath = "Auron/Shaders/glsl/shader.frag";

        GLsizei stride = sizeof(Vert);

        material = new GLSLShader();
        material->LoadFromFile(vertexShaderSourcePath, ShaderType::VERTEX);
        material->LoadFromFile(fragmentShaderSourcePath, ShaderType::FRAGMENT);
        material->CreateProgram();
        // material->Use();
            // material->AddAttribute("vVertex");
        // material->StopUsing();
        
        // glEnableVertexAttribArray((*material)["vVertex"]);
        // glVertexAttribPointer((*material)["vVertex"], 3, GL_FLOAT, GL_FALSE, stride, 0);
            // material->AddAttribute("vColor");
            // material->AddUniform("MVP");
        // glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(int), indices.data(), GL_STATIC_DRAW);
    }
    
    SceneObject::~SceneObject()
    {
        delete material;
    }

     std::vector<float>* SceneObject::GetVertices()
    {
        return &vertices;
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
