// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "Source/Core/Window.h"
#include <GLFW/glfw3.h>

namespace Auron {
    class WinWindow: public Window
    {
    private:
        GLFWwindow* m_Window;
        WindowSettings* m_Settings;
    public:
        WinWindow(WindowSettings* settings);
        ~WinWindow();
        virtual bool Initialize() override;
        virtual void Update() override;
        virtual void Terminate() override;
        virtual bool ShouldClose() override;
    };
}