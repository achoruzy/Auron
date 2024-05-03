// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#define GLFW_INCLUDE_NONE
#include "GLRenderer.h"
#include "Source/Core/Logger.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Auron::GLRenderer::Initialize()
{
    int ver = gladLoadGL();
    if (ver == 0)
    {
        LOG_CRITICAL("OpenGL context couldn't be initialized.");
    }
    LOG_INFO("Initialized OpenGL ver. {0}.{1}", GLVersion.major, GLVersion.minor);
}

void Auron::GLRenderer::Update()
{
    glClear(GL_COLOR_BUFFER_BIT);
}