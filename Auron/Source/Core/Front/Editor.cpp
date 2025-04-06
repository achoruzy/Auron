// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "Editor.h"
#include "../Window.h"
#include "Menu.h"
#include "Tools.h"
#include "RMBMenu.h"
#include "CommandConsole.h"
#include "Widgets.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>

namespace Auron {

    Editor* Editor::single_Instance = nullptr;

    Editor::Editor()
    {
        if (single_Instance != nullptr)
        {
            single_Instance = this;
        }
        m_CommandConsole = new CommandConsole();
    }

    Editor::~Editor()
    {
        delete m_CommandConsole;
    }

    int Editor::Initialize(Window* ActiveWindow)
    {
        IMGUI_CHECKVERSION();
        m_ImGuiContext = ImGui::CreateContext();
        m_ImGuiIO = &(ImGui::GetIO());

        m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui::StyleColorsDark();
        bool isInitializedGL = ImGui_ImplOpenGL3_Init();
        bool isInitializedGLFW = ImGui_ImplGlfw_InitForOpenGL(ActiveWindow->GetWindow(), true);

        // Add some example commands
        m_CommandConsole->AddCommand("echo", [](const std::vector<std::string>& args) {
            for (const auto& arg : args) {
                // LOG_GAME_INFO("Echo: %s", arg.c_str());
                std::cout << "Echo: " << arg << std::endl;
            }
        });

        if (m_ImGuiContext && m_ImGuiIO && isInitializedGL && isInitializedGLFW) return true;
        return false;
    }
    
    void Editor::Update()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ImGui DEMO
        // ImGui::ShowDemoWindow();
        
        RMBMenu menuInstance;
        menuInstance.RegisterMenuOption("Object1", "Option 1", []() { std::cout << "Option 1 selected!\n"; });
        
        Menu::Render();
        ToolsBar::Render();
        // CommandConsole::Draw();
        

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
        {
            HandleRightClickMenu(); // Replace "ObjectID" with the actual object ID you want to show the menu for
        }

        m_CommandConsole->Draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Editor::HandleRightClickMenu()
    {
        static bool isMenuOpen = false;
        static std::string activeObjectID;

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
        {
            isMenuOpen = true;
            activeObjectID = "Object1"; // Replace with the actual object ID
        }

        if (isMenuOpen)
        {
            RMBMenu menuInstance;
            menuInstance.RegisterMenuOption("Object1", "Option 1", []() { std::cout << "Option 1 selected!\n"; });
            menuInstance.HandleRightClick(activeObjectID);

            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                isMenuOpen = false;
            }
        }
    }
}