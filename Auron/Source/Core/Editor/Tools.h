#pragma once

#include "imgui.h"
#include <string>
#include <unordered_map>
#include <vector>

// Tooltip helper function
void ShowTooltip(const char* tooltip) {
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("%s", tooltip);
    }
}
// Helper function to load textures (implement this based on your rendering backend)
unsigned int LoadTexture(const char* path) {
    // Load the texture and return its ID
    // Implementation depends on your graphics API (e.g., OpenGL, DirectX, Vulkan)
    return 0; // Placeholder
}
// Helper function to render a card with buttons
static void RenderCard(const char* title, const std::vector<std::pair<const char*, const char*>>& buttons) {
    // ImGui::BeginChild(title, ImVec2(200, 0), true, ImGuiWindowFlags_NoResize);
    // ImGui::Text("%s", title);
    ImGui::Separator();

    for (const auto& button : buttons) {
        if (ImGui::ImageButton((void*)(intptr_t)LoadTexture(button.second), ImVec2(32, 32))) {
            // Handle button action
        }
        ShowTooltip(button.first);
        ImGui::SameLine();
    }
    ImGui::NewLine(); // Move to the next row
    // ImGui::EndChild();
}

// Helper function to render tabs
static void RenderTabs(const std::unordered_map<std::string, std::vector<std::pair<const char*, const char*>>>& tabs) {
    static std::string activeTab = tabs.begin()->first; // Default to the first tab

    // Render tab menu
    // ImGui::BeginChild("TabMenu", ImVec2(0, 30), false, ImGuiWindowFlags_NoResize);
    for (const auto& tab : tabs) {
        if (ImGui::Button(tab.first.c_str())) {
            activeTab = tab.first; // Switch active tab
        }
        ImGui::SameLine();
    }
    // ImGui::EndChild();

    ImGui::Separator();

    // Render active tab content
    auto it = tabs.find(activeTab);
    if (it != tabs.end()) {
        RenderCard(it->first.c_str(), it->second);
    }
}

class ToolsBar {
public:
    static void Render() {
        // Begin a toolbar window
        ImGui::Begin("Tools Bar", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);


        // Define tabs and their content
        std::unordered_map<std::string, std::vector<std::pair<const char*, const char*>>> tabs = {
            {"Tools", {{"Select Tool", "icons/select.png"}, {"Move Tool", "icons/move.png"}}},
            {"Actions", {{"Delete", "icons/delete.png"}, {"Duplicate", "icons/duplicate.png"}}}
        };

        // Render the tabs
        RenderTabs(tabs);


        // Set toolbar size and position
        ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 80)); // Full width, fixed height
        ImGui::SetWindowPos(ImVec2(0, 20)); // Position below the menu bar

        // // Add tool buttons with icons
        // if (ImGui::ImageButton((void*)(intptr_t)LoadTexture("icons/select.png"), ImVec2(32, 32))) {
        //     // Handle Select action
        // }
        // ShowTooltip("Select Tool");

        // ImGui::SameLine();
        // if (ImGui::ImageButton((void*)(intptr_t)LoadTexture("icons/move.png"), ImVec2(32, 32))) {
        //     // Handle Move action
        // }
        // ImGui::SameLine();
        // if (ImGui::ImageButton((void*)(intptr_t)LoadTexture("icons/rotate.png"), ImVec2(32, 32))) {
        //     // Handle Rotate action
        // }
        // ImGui::SameLine();
        // if (ImGui::ImageButton((void*)(intptr_t)LoadTexture("icons/scale.png"), ImVec2(32, 32))) {
        //     // Handle Scale action
        // }

        // // Separator
        // ImGui::SameLine();
        // ImGui::Dummy(ImVec2(10, 0)); // Add spacing

        // // Add more tool buttons
        // if (ImGui::ImageButton((void*)(intptr_t)LoadTexture("icons/pan.png"), ImVec2(32, 32))) {
        //     // Handle Pan action
        // }
        // ImGui::SameLine();
        // if (ImGui::ImageButton((void*)(intptr_t)LoadTexture("icons/zoom.png"), ImVec2(32, 32))) {
        //     // Handle Zoom action
        // }

        ImGui::End();
    }

private:
    // Helper function to load textures (implement this based on your rendering backend)
    static unsigned int LoadTexture(const char* path) {
        // Load the texture and return its ID
        // Implementation depends on your graphics API (e.g., OpenGL, DirectX, Vulkan)
        return 0; // Placeholder
    }
};