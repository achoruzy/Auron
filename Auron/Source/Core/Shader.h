// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include <string>
#include <map>
#include <glad/glad.h>
#include <glm/glm.hpp>

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
        virtual bool HasAttribute(const std::string& attribute) = 0;
        virtual void AddUniform(const std::string& uniform) = 0;
        virtual void SetUniformInt(const std::string& uniform, const int value) = 0;
        virtual void SetUniformFloat(const std::string& uniform, const float value) = 0;
        virtual void SetUniformVec2(const std::string& uniform, const glm::vec2& value) = 0;
        virtual void SetUniformVec3(const std::string& uniform, const glm::vec3& value) = 0;
        virtual void SetUniformVec4(const std::string& uniform, const glm::vec4& value) = 0;
        virtual void SetUniformMat4(const std::string& uniform, const glm::mat4& value) = 0;
        virtual void DeleteProgram() = 0;
    };
}