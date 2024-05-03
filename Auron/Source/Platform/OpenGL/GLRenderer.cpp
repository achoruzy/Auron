// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#define GLFW_INCLUDE_NONE
#include "GLRenderer.h"
#include "Source/Core/Logger.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Auron {
    GLRenderer::GLRenderer(GLFWwindow* window)
    {
        m_Window = window;
    }

    GLRenderer::~GLRenderer()
    {
    }

    void GLRenderer::Initialize()
    {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        // if (gladLoadGL() != 0)
        {
            LOG_CRITICAL("OpenGL context couldn't be initialized.");
        }
        LOG_INFO("Initialized OpenGL ver. {0}.{1}", GLVersion.major, GLVersion.minor);
    }

    /// @brief  Per frame rendering pipeline. To be called in main loop.
    void GLRenderer::Update()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    void GLRenderer::UpdateViewport(int x, int y, int w, int h)
    {
        glViewport(x, y, w, h);
    }
}