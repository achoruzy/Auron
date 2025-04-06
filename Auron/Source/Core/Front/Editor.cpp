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
        : m_isDrawingLine(false)
        , m_currentLineColor(1.0f, 1.0f, 1.0f, 1.0f)
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

        // Add line drawing commands
        m_CommandConsole->AddCommand("line_color", [this](const std::vector<std::string>& args) {
            if (args.size() >= 3) {
                try {
                    float r = std::stof(args[0]);
                    float g = std::stof(args[1]);
                    float b = std::stof(args[2]);
                    m_currentLineColor = ImVec4(r, g, b, 1.0f);
                    std::cout << "Line color set to: " << r << ", " << g << ", " << b << std::endl;
                } catch (...) {
                    std::cout << "Invalid color values. Usage: line_color r g b (values 0-1)" << std::endl;
                }
            } else {
                std::cout << "Usage: line_color r g b (values 0-1)" << std::endl;
            }
        });

        m_CommandConsole->AddCommand("clear_lines", [this](const std::vector<std::string>&) {
            ClearLines();
            std::cout << "All lines cleared" << std::endl;
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
        
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
        {
            HandleRightClickMenu();
        }

        HandleLineDrawing();
        m_CommandConsole->Draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Editor::HandleLineDrawing()
    {
        ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
        
        // Draw existing lines
        for (const auto& line : m_lines) {
            draw_list->AddLine(
                ImVec2(line.start.x, line.start.y),
                ImVec2(line.end.x, line.end.y),
                ImColor(line.color),
                2.0f
            );
        }

        // Handle line drawing
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            if (!m_isDrawingLine) {
                // Start new line
                m_isDrawingLine = true;
                m_currentLineStart = glm::vec2(ImGui::GetMousePos().x, ImGui::GetMousePos().y);
            } else {
                // Complete the line
                m_isDrawingLine = false;
                glm::vec2 end = glm::vec2(ImGui::GetMousePos().x, ImGui::GetMousePos().y);
                m_lines.push_back({m_currentLineStart, end, m_currentLineColor});
            }
        }

        // Draw current line being drawn
        if (m_isDrawingLine) {
            glm::vec2 current = glm::vec2(ImGui::GetMousePos().x, ImGui::GetMousePos().y);
            draw_list->AddLine(
                ImVec2(m_currentLineStart.x, m_currentLineStart.y),
                ImVec2(current.x, current.y),
                ImColor(m_currentLineColor),
                2.0f
            );
        }
    }

    void Editor::ClearLines()
    {
        m_lines.clear();
    }

    void Editor::HandleRightClickMenu()
    {
        static bool isMenuOpen = false;
        static std::string activeObjectID;

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
        {
            isMenuOpen = true;
            activeObjectID = "Object1";
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