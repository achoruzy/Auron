// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "GLSLShader.h"
#include "Source/Core/Logger.h"
#include <GLFW/glfw3.h>

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

    void GLSLShader::SetUniformInt(const std::string &uniform, const int value)
    {
        glUniform1i(uniforms[uniform], value);
    }

    void GLSLShader::SetUniformFloat(const std::string &uniform, const float value)
    {
        glUniform1f(uniforms[uniform], value);
    }

    void GLSLShader::SetUniformVec2(const std::string &uniform, const glm::vec2 &value)
    {
        glUniform2fv(uniforms[uniform], 1, &value[0]);
    }

    void GLSLShader::SetUniformVec3(const std::string &uniform, const glm::vec3 &value)
    {
        glUniform3fv(uniforms[uniform], 1, &value[0]);
    }  

    void GLSLShader::SetUniformVec4(const std::string &uniform, const glm::vec4 &value)
    {
        glUniform4fv(uniforms[uniform], 1, &value[0]);
    }

    void GLSLShader::SetUniformMat4(const std::string &uniform, const glm::mat4 &value)
    {
        glUniformMatrix4fv(uniforms[uniform], 1, GL_FALSE, &value[0][0]);
    }
}