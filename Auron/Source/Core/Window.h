// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "Renderer.h"
#include "Input.h"
#include <string>
#include <GLFW/glfw3.h>


namespace Auron { 
    class Window
    {
    public:
        virtual bool Initialize(Renderer* renderer, Input* input) = 0;
        virtual void Update() = 0;
        virtual void Terminate() = 0;
        virtual bool ShouldClose() = 0;
        virtual GLFWwindow* GetWindow() = 0;
    };
}