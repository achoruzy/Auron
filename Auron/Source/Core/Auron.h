// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "Window.h"
#include "Renderer.h"

namespace Auron {
    /// @brief Base engine initialization and work class.
    class Auron
    {
    private:
        static Auron* single_Instance;
        Window* m_Window;
        Input* m_Input;
        Renderer* m_Renderer;

    public:
        Auron();
        ~Auron();
        static Auron& Get() { return *single_Instance; }

        int Initialize();
        void Run();
    
    };
}