// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "WinWindow.h"
#include <GLFW/glfw3.h>
#include "Source/Core/Logger.h"
#include "Source/Core/Renderer.h"
#include "Source/Core/WindowSettings.h"
#include <GLFW/glfw3.h>


namespace Auron {

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    WinWindow::WinWindow(WindowSettings* settings)
    {
        m_Settings = settings;
    }

    WinWindow::~WinWindow()
    {
    }

    bool WinWindow::Initialize(Renderer* renderer, Input* input)
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
        renderer->Initialize();
        renderer->UpdateViewport(w, h);

        // BINDING APP CALLBACKS
        glfwSetWindowUserPointer(m_Window, renderer);
        glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
            if (renderer)
            {
                renderer->UpdateViewport(width, height);
            }
        });

        // BINDING INPUT CALLBACKS
        glfwSetWindowUserPointer(m_Window, input);
        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
            if (input)
            {
                input->OnKeyCallback(key, scancode, action, mods);
            }
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
            Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
            if (input)
            {
                input->OnCursorCallback(xpos, ypos);
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
            if (input)
            {
                input->OnMouseButtonCallback(button, action, mods);
            }
        });


        return true;
    }

    void WinWindow::Update()
    {
        glfwSwapBuffers(m_Window);
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
}