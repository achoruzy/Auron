// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "Auron.h"
#include "Logger.h"
#include <GLFW/glfw3.h>

namespace Auron {

    Auron* Auron::single_Instance = nullptr;

    Auron::Auron()
    {
        if (single_Instance != nullptr)
        {
            single_Instance = this;
        }
    }

    Auron::~Auron()
    {
    }

    int Auron::Initialize()
    {
        Logger::Initialize();

        GLFWwindow* Window;
        if (!glfwInit())
        {
            return -1;
        }
        Window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

        if (!Window)
        {
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(Window);
        while(!glfwWindowShouldClose(Window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(Window);
            glfwPollEvents();
        }
        glfwTerminate();
        return 0;
    }
}