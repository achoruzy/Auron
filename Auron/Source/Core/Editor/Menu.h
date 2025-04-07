#pragma once

#include "imgui.h"

class Menu
{
public:
    static void Render()
    {
        // Create a fixed top menu bar
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New")) { /* Handle New */ }
                if (ImGui::MenuItem("Open")) { /* Handle Open */ }
                if (ImGui::MenuItem("Save")) { /* Handle Save */ }
                if (ImGui::MenuItem("Exit")) { /* Handle Exit */ }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo")) { /* Handle Undo */ }
                if (ImGui::MenuItem("Redo")) { /* Handle Redo */ }
                if (ImGui::MenuItem("Cut")) { /* Handle Cut */ }
                if (ImGui::MenuItem("Copy")) { /* Handle Copy */ }
                if (ImGui::MenuItem("Paste")) { /* Handle Paste */ }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("About")) { /* Handle About */ }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }
};