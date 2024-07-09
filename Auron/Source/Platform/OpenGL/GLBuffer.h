// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "Source/Core/RenderBuffer.h"
#include <map>
#include <vector>
#include <string>
#include <glad/glad.h>


namespace Auron { 
    class SceneObject;
    class Shader;
    class Vert;
    class GLSLShader;

    class GLBuffer : RenderBuffer
    {
    private:
        GLuint VBO;
        GLuint VAO;
        GLuint EBO;
        SceneObject* object;
        Vert* vertices;
        unsigned int vertices_count;
        std::vector<unsigned int>* indices; // TODO: weird type as no struct yet made
        unsigned int indices_count;
        Shader* shader;

    public:
        GLBuffer(SceneObject* object, Shader* shader);
        ~GLBuffer();
        virtual void DrawObject() override;
    
    private:
        void Initialize();
        void GenerateBuffers();

        void SetAttributeEnabled(const std::string& attribute);
    };
}