// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "GLSLShader.h"
#include "Source/Core/Logger.h"

namespace Auron {
    GLuint GLSLShader::operator[](const std::string &attribute)
    {
        return attributes[attribute];
    }

    GLuint GLSLShader::operator()(const std::string &uniform)
    {
        return uniforms[uniform];
    }

    void GLSLShader::CreateProgram()
    {
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

    void GLSLShader::Use()
    {
        glUseProgram(shaderProgram);
    }

    void GLSLShader::StopUsing()
    {
        glUseProgram(0);
    }

    void GLSLShader::DeleteProgram()
    {
        glDeleteProgram(shaderProgram);
    }

    void GLSLShader::AddAttribute(const std::string &attribute)
    {
        GLuint location = glGetAttribLocation(shaderProgram, attribute.c_str());
        if (location == -1)
        {
            LOG_ERROR("Shader attribute not found: {0}", attribute);
        }
        else
        {
            attributes[attribute] = location;
        }
    }

    void GLSLShader::AddUniform(const std::string &uniform)
    {
        GLuint location = glGetUniformLocation(shaderProgram, uniform.c_str());
        if (location == -1)
        {
            LOG_ERROR("Shader uniform not found: {0}", uniform);
        }
        else
        {
            uniforms[uniform] = location;
        }
    }
}