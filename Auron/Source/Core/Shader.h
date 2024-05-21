// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include <string>
#include <map>


namespace Auron {
    enum class ShaderType
    {
        VERTEX,
        FRAGMENT
    };

    class Shader
    {
    protected:
        std::map<ShaderType, unsigned int> shaders;
    public:
        void LoadFromFile(std::string& shaderPath, ShaderType shaderType);
        void LoadFromString(std::string& shaderCode, ShaderType shaderType);
        virtual void CreateProgram() = 0;
        virtual void Use() = 0;
        virtual void StopUsing() = 0;
        virtual void AddAttribute(const std::string& attribute) = 0;
        virtual void AddUniform(const std::string& uniform) = 0;
        virtual void DeleteProgram() = 0;
    };
}