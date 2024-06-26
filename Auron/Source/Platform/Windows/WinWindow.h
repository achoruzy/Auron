// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "Source/Core/Window.h"

class GLFWwindow;

namespace Auron {
    class WindowSettings;

    class WinWindow: public Window
    {
    private:
        GLFWwindow* m_Window;
        WindowSettings* m_Settings;
    public:
        WinWindow(WindowSettings* settings);
        ~WinWindow();
        // window related
        virtual bool Initialize(Renderer* renderer, Input* input) override;
        virtual void Update() override;
        virtual void Terminate() override;
        virtual bool ShouldClose() override;
        virtual GLFWwindow* GetWindow() override;
    };
}