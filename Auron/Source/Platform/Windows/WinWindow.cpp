// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "WinWindow.h"
#include <GLFW/glfw3.h>

namespace Auron {
    Auron::WinWindow::WinWindow(WindowSettings* settings)
    {
        m_Settings = settings;
    }

    Auron::WinWindow::~WinWindow()
    {
    }

    bool Auron::WinWindow::Initialize()
    {
        if (!glfwInit()) { return false; }

        m_Window = glfwCreateWindow(m_Settings->Width, m_Settings->Height, m_Settings->Title.c_str(), NULL, NULL);

        if (!m_Window)
        {
            Terminate();
            return false;
        }

        glfwMakeContextCurrent(m_Window);
        return true;
    }

    void Auron::WinWindow::Update()
    {
        glfwSwapBuffers(m_Window);
    }

    void Auron::WinWindow::Terminate()
    {
        glfwTerminate();
    }

    bool Auron::WinWindow::ShouldClose()
    {
        return glfwWindowShouldClose(m_Window);
    }
}