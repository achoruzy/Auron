// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "Source/Core/Shader.h"
#include <string>
#include <map>
#include <glad/glad.h>


namespace Auron { 
    class GLSLShader : public Shader
    {
    private:
        GLuint shaderProgram;
        
        std::map<std::string, GLuint> attributes;
        std::map<std::string, GLuint> uniforms;
    public:
        virtual GLuint operator[] (const std::string& attribute);
        virtual GLuint operator() (const std::string& uniform);
        virtual void CreateProgram() override;
        virtual void Use() override;
        virtual void StopUsing() override;
        virtual void AddAttribute(const std::string& attribute) override;
        virtual void AddUniform(const std::string& uniform) override;
        virtual void SetUniformInt(const std::string& uniform, const int value) override;
        virtual void SetUniformFloat(const std::string& uniform, const float value) override;
        virtual void SetUniformVec2(const std::string& uniform, const glm::vec2& value) override;
        virtual void SetUniformVec3(const std::string& uniform, const glm::vec3& value) override;
        virtual void SetUniformVec4(const std::string& uniform, const glm::vec4& value) override;
        virtual void SetUniformMat4(const std::string& uniform, const glm::mat4& value) override;
        virtual void DeleteProgram() override;
    };
}