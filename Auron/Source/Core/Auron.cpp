// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "Auron.h"
#include "Logger.h"
#include "Window.h"
#include "Source/Platform/OpenGL/GLRenderer.h"
#include "Source/Platform/Windows/WinWindow.h"
#include "Source/Platform/Windows/WinInput.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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
    }

    int Auron::Initialize()
    {
        Logger::Initialize();

        WindowSettings WinSettings;
        m_Renderer = new GLRenderer();
        m_Input = new WinInput();
        m_Window = new WinWindow(&WinSettings);

        if (m_Window->Initialize(m_Renderer, m_Input))
        {
            LOG_GAME_INFO("Window initialized properly.");
        }
        else {
            LOG_CRITICAL("Window couldn't be initialized.");
        }

        return 0;
    }

    // Main application loop
    void Auron::Run()
    {
        bool my_tool_active = true;

            // IMGUI DEMO
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

            // Setup Dear ImGui style
            ImGui::StyleColorsDark();
            //ImGui::StyleColorsLight();
            ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindow(), true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
            ImGui_ImplOpenGL3_Init();

        while (!m_Window->ShouldClose())
        {
            m_Input->Poll();
            m_Window->Update();
            m_Renderer->Update();

            // IMGUI DEMO
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGui::ShowDemoWindow(); // Show demo window! :)

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
    }
}