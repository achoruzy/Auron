// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "GLSLShader.h"
#include "Source/Core/Logger.h"

namespace Auron {
    void GLSLShader::CreateProgram()
    {
        const char *vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main() { gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); }\0";
        
        const char *fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main() { FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); } \0";


        vertShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertShader);

        // shader compilation debug
        
        int  success;
        char infoLog[512];
        glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
            LOG_ERROR("Vertex shader compilation failed: %s", infoLog);
        }

        
        fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragShader);

        int  successFrag;
        char infoLogFrag[512];
        glGetShaderiv(vertShader, GL_COMPILE_STATUS, &successFrag);
        if(!successFrag)
        {
            glGetShaderInfoLog(fragShader, 512, NULL, infoLogFrag);
            LOG_ERROR("Fragment shader compilation failed: %s", infoLogFrag);
        }

        // shader program ========
        shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, vertShader);
        glAttachShader(shaderProgram, fragShader);
        glLinkProgram(shaderProgram);

        int  successLink;
        char infoLogLink[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successLink);
        if(!successLink) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLogLink);
            LOG_ERROR("Shader program linking failed: %s", infoLogLink);
        }

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
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

    void GLSLShader::AddAttribute(const std::string &attribute)
    {
    }

    void GLSLShader::DeleteProgram()
    {
    }

    void GLSLShader::AddUniform(const std::string &uniform)
    {
    }
}