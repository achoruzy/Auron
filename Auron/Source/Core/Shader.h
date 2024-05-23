// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include <string>
#include <map>
#include <glad/glad.h>

namespace Auron {
    enum class ShaderType
    {
        VERTEX,
        FRAGMENT
    };

    class Shader
    {
    protected:
        std::map<ShaderType, GLuint> shaders;
    public:
        void LoadFromFile(std::string& shaderPath, ShaderType shaderType);
        void LoadFromString(std::string& shaderCode, ShaderType shaderType);
        virtual GLuint operator[](const std::string& attribute) = 0;
        virtual GLuint operator()(const std::string& uniform) = 0;
        virtual void CreateProgram() = 0;
        virtual void Use() = 0;
        virtual void StopUsing() = 0;
        virtual void AddAttribute(const std::string& attribute) = 0;
        virtual void AddUniform(const std::string& uniform) = 0;
        virtual void DeleteProgram() = 0;
    };
}