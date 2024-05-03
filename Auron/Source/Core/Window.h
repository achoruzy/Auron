// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include <string>
#include <GLFW/glfw3.h>


namespace Auron { 
    class Window
    {
    public:
        virtual bool Initialize() = 0;
        virtual void Update() = 0;
        virtual void Terminate() = 0;
        virtual bool ShouldClose() = 0;
        virtual GLFWwindow* GetWindow() = 0;
        virtual void Poll() = 0;
    };
}