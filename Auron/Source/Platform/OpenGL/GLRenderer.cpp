// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#define GLFW_INCLUDE_NONE
#include "GLRenderer.h"
#include "Source/Core/Logger.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLBuffers.h"
#include "Source/Core/Scene/SceneObject.h"

namespace Auron {
    GLRenderer::GLRenderer()
    {
    }

    GLRenderer::~GLRenderer()
    {
    }

    void GLRenderer::Initialize()
    {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            LOG_CRITICAL("OpenGL context couldn't be initialized.");
        }
        LOG_INFO("Initialized OpenGL ver. {0}.{1}", GLVersion.major, GLVersion.minor);
    }

    /// @brief  Per frame rendering pipeline. To be called in main loop.
    void GLRenderer::Update()
    {
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        GLBuffers buffers = GLBuffers();
        buffers.DrawObject(new SceneObject()); // TODO
    }
    
    void GLRenderer::UpdateViewport(const int w, const int h) const
    {
        glViewport(0, 0, w, h);
    }
}