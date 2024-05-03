// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "WinWindow.h"
#include <GLFW/glfw3.h>
#include "Source/Core/Logger.h"

namespace Auron {
    WinWindow::WinWindow(WindowSettings* settings)
    {
        m_Settings = settings;
    }

    WinWindow::~WinWindow()
    {
    }

    bool WinWindow::Initialize()
    {
        if (!glfwInit()) { return false; }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
        
        m_Window = glfwCreateWindow(m_Settings->Width, m_Settings->Height, m_Settings->Title.c_str(), NULL, NULL);

        if (!m_Window)
        {
            Terminate();
            return false;
        }

        glfwMakeContextCurrent(m_Window);
        int w, h;
        glfwGetFramebufferSize(m_Window, &w, &h);
        glViewport(0, 0, w, h); // TODO to change

        // BINDING CALLBACKS
        glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        });

        return true;
    }

    void WinWindow::Update()
    {
        glfwSwapBuffers(m_Window);
        Poll();
    }

    void WinWindow::Terminate()
    {
        glfwTerminate();
    }

    bool WinWindow::ShouldClose()
    {
        return glfwWindowShouldClose(m_Window);
    }

    GLFWwindow* WinWindow::GetWindow()
    {
        return m_Window;
    }

    void WinWindow::Poll()
    {
        glfwPollEvents();
    }
}