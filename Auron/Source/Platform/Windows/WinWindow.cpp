// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "WinWindow.h"
#include <GLFW/glfw3.h>

namespace Auron {
    WinWindow::WinWindow(WindowSettings* settings)
    {
        Settings = settings;
    }

    WinWindow::~WinWindow()
    {
    }

    bool WinWindow::Initialize()
    {
        GLFWwindow* Window;
        if (!glfwInit())
        {
            return false;
        }
        Window = glfwCreateWindow(Settings->Width, Settings->Height, Settings->Title.c_str(), NULL, NULL);

        if (!Window)
        {
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(Window);
        while(!glfwWindowShouldClose(Window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(Window);
            glfwPollEvents();
        }
        glfwTerminate();
        return true;
    }
}