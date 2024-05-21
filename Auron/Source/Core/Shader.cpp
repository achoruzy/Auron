// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "Shader.h"
#include "Source/Core/Logger.h"
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <glad/glad.h>



void Auron::Shader::LoadFromFile(std::string& shaderPath, ShaderType shaderType)
{
    std::ifstream fs(shaderPath);
    if (!fs)
    {
        LOG_ERROR("Shader load from string error: Couldn't be loaded file: {0}", shaderPath);
        return;
    }
    std::ostringstream sbuff;
    sbuff << fs.rdbuf();

    std::string shaderCode = sbuff.str();
    LoadFromString(shaderCode, shaderType);

}

void Auron::Shader::LoadFromString(std::string& shaderCode, ShaderType shaderType)
{
    // TODO: validation?
    const char* source = shaderCode.c_str();

    int creationType;
    switch (shaderType)
    {
    case ShaderType::VERTEX:
        creationType = GL_VERTEX_SHADER;
        break;
    case ShaderType::FRAGMENT:
        creationType = GL_FRAGMENT_SHADER;
        break;
    default:
        LOG_ERROR("Shader type is not implemented to be handled!");
        break;
    }

    shaders[shaderType] = glCreateShader(creationType);
    glShaderSource(shaders[shaderType], 1, &source, NULL);
    glCompileShader(shaders[shaderType]);

    // shader compilation debug
    int  success;
    char infoLog[512];
    glGetShaderiv(shaders[shaderType], GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shaders[shaderType], 512, NULL, infoLog);
        LOG_ERROR("Shader compilation failed: {0}", infoLog);
    }
}