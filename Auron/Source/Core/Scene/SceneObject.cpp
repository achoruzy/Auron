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
        // TODO: -> component and stack
        // m_vertices = {
        //     0.5f,  0.5f, 0.0f,  // top right
        //     0.5f, -0.5f, 0.0f,  // bottom right
        //     -0.5f, -0.5f, 0.0f,  // bottom left
        //     -0.5f,  0.5f, 0.0f   // top left
        // };
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

        glm::mat4 P = glm::ortho(-1,1,-1,1);
        glm::mat4 MV = glm::mat4(1);
        GLsizei stride = sizeof(Vert);

        std::string vertexShaderSourcePath = "Auron/Shaders/glsl/shader.vert";
        std::string fragmentShaderSourcePath = "Auron/Shaders/glsl/shader.frag";

        material = new GLSLShader();
        material->LoadFromFile(vertexShaderSourcePath, ShaderType::VERTEX);
        material->LoadFromFile(fragmentShaderSourcePath, ShaderType::FRAGMENT);
        material->CreateProgram();

        material->Use();
            material->AddAttribute("vVertex");
            material->AddAttribute("vColor");
            material->AddUniform("MVP");

            glEnableVertexAttribArray((*material)["vVertex"]);
            glVertexAttribPointer((*material)["vVertex"], 3, GL_FLOAT, GL_FALSE, stride, 0);
            // GL_CHECK_ERRORS
            //enable vertex attribute array for colour
            glEnableVertexAttribArray((*material)["vColor"]);
            glVertexAttribPointer((*material)["vColor"], 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offsetof(Vert, color));
            // GL_CHECK_ERRORS
            glUniformMatrix4fv((*material)("MVP"), 1, GL_FALSE, glm::value_ptr(P*MV));

            
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
