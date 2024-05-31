// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#define GLFW_INCLUDE_NONE

#include "GLRenderer.h"
#include "GLBuffer.h"
#include "Source/Core/Logger.h"
#include "Source/Core/Scene/SceneObject.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // TODO: Use Scene class (to do) here for getting scene objects
        // TEST ================================
        SceneObject object{};
        GLBuffer buffer{&object, object.GetMaterial()};
        object.GetMaterial()->Use();
            buffer.DrawObject();
        object.GetMaterial()->StopUsing();
    }
    
    void GLRenderer::UpdateViewport(const int w, const int h) const
    {
        glViewport(0, 0, w, h);
    }
}