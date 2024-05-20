// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "Source/Core/Shader.h"
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>


namespace Auron { 
    class GLSLShader : public Shader
    {
    private:
        GLuint vertShader;
        GLuint fragShader;
        GLuint shaderProgram;

        std::map<std::string, GLuint> attributes;
        std::map<std::string, GLuint> uniforms;
    public:
        virtual void CreateProgram() override;
        virtual void Use() override;
        virtual void StopUsing() override;
        virtual void AddAttribute(const std::string& attribute) override;
        virtual void AddUniform(const std::string& uniform) override;
        virtual void DeleteProgram() override;
    };
}