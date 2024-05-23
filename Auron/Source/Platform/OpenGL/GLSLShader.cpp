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

        // for (auto const& [type, shader] : shaders)
        // {
        //     glDeleteShader(shader);
        // }
    }

    void Auron::GLSLShader::Use()
    {
        // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0); // vertex data
        // glEnableVertexAttribArray(0);
        // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0); // vertex color data
        // glEnableVertexAttribArray(1);

        glUseProgram(shaderProgram);
    }

    void GLSLShader::StopUsing()
    {
        glUseProgram(0);
    }

    void GLSLShader::DeleteProgram()
    {
        for (auto const& [type, shader] : shaders)
        {
            glDeleteShader(shader);
        }
        glDeleteProgram(shaderProgram);
    }

    void GLSLShader::AddAttribute(const std::string &attribute)
    {
        attributes[attribute] = glGetAttribLocation(shaderProgram, attribute.c_str());
    }

    void GLSLShader::AddUniform(const std::string &uniform)
    {
        uniforms[uniform] = glGetUniformLocation(shaderProgram, uniform.c_str());
    }
}