// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "Auron.h"
#include "Logger.h"
#include "Window.h"
#include "Source/Platform/Windows/WinWindow.h"
// #include <GLFW/glfw3.h>

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

        WindowSettings WinSettings;
        auto Window = WinWindow(&WinSettings);
        Window.Initialize();

        return 0;
    }
}