// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "Auron.h"
#include "Window.h"
#include "Renderer.h"
#include "Logger.h"
#include "Front/Editor.h"
#include "Source/Core/WindowSettings.h"
#include "Source/Platform/OpenGL/GLRenderer.h"
#include "Source/Platform/Windows/WinWindow.h"
#include "Source/Platform/Windows/WinInput.h"

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
        delete m_Input;
        delete m_Editor;
    }

    int Auron::Initialize()
    {
        Logger::Initialize();

        WindowSettings WinSettings;
        m_Renderer = new GLRenderer();
        m_Input = new WinInput();
        m_Window = new WinWindow(&WinSettings);
        m_Editor = new Editor();

        if (m_Window->Initialize(m_Renderer, m_Input))
        {
            LOG_GAME_INFO("Window initialized properly.");
        }
        else {
            LOG_CRITICAL("Window couldn't be initialized.");
        }

        if (m_Editor->Initialize(m_Window))
        {
            LOG_GAME_INFO("Editor initialized properly.");
        }
        else {
            LOG_CRITICAL("Editor couldn't be initialized.");
        }

        return 0;
    }

    // Main application loop
    void Auron::Run()
    {
        while (!m_Window->ShouldClose())
        {
            m_Input->Poll();
            m_Window->Update();
            m_Renderer->Update();
            m_Editor->Update();
        }
    }
}