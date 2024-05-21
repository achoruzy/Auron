// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "GLSLShader.h"
#include "Source/Core/Logger.h"

namespace Auron {
    void GLSLShader::CreateProgram()
    {
        std::string vertexShaderSourcePath = "Auron/Shaders/glsl/shader.vert";
        std::string fragmentShaderSourcePath = "Auron/Shaders/glsl/shader.frag";

        LoadFromFile(vertexShaderSourcePath, ShaderType::VERTEX);
        LoadFromFile(fragmentShaderSourcePath, ShaderType::FRAGMENT);

        // shader program ========
        shaderProgram = glCreateProgram();

        for (auto const& [type, shader] : shaders)
        {
            glAttachShader(shaderProgram, shader);
        }
        glLinkProgram(shaderProgram);

        int  successLink;
        char infoLogLink[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successLink);
        if(!successLink) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLogLink);
            LOG_ERROR("Shader program linking failed: {0}", infoLogLink);
        }

        for (auto const& [type, shader] : shaders)
        {
            glDeleteShader(shader);
        }
    }

    void Auron::GLSLShader::Use()
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0); // vertex data
        glEnableVertexAttribArray(0);

        glUseProgram(shaderProgram);
    }

    void GLSLShader::StopUsing()
    {
    }

    void GLSLShader::DeleteProgram()
    {
    }

    void GLSLShader::AddAttribute(const std::string &attribute)
    {
    }

    void GLSLShader::AddUniform(const std::string &uniform)
    {
    }
}