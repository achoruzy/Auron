// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "Auron.h"
#include "Logger.h"
#include "Window.h"
#include "Source/Platform/OpenGL/GLRenderer.h"
#include "Source/Platform/Windows/WinWindow.h"

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
        delete m_Window;
        delete m_Renderer;
    }

    int Auron::Initialize()
    {
        Logger::Initialize();

        WindowSettings WinSettings;
        m_Window = new WinWindow(&WinSettings);
        auto window = m_Window->GetWindow();
        m_Renderer = new GLRenderer(window);

        if (m_Window->Initialize())
        {
            m_Renderer->Initialize();
        }
        else {
            LOG_CRITICAL("Window couldn't be initialized.");
        }

        return 0;
    }

    // Main application loop
    void Auron::Run()
    {
        while (!m_Window->ShouldClose())
        {
            m_Window->Update();
            m_Renderer->Update();
        }
    }
}