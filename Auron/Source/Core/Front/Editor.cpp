// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "Editor.h"
#include "../Window.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Auron {

    Editor* Editor::single_Instance = nullptr;

    Editor::Editor()
    {
        if (single_Instance != nullptr)
        {
            single_Instance = this;
        }
    }

    Editor::~Editor()
    {
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

        if (m_ImGuiContext && m_ImGuiIO && isInitializedGL && isInitializedGLFW) return true;
        return false;
    }

    void Editor::Update()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}