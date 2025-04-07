#pragma once

#include "imgui.h"
#include <string>
#include <functional>

namespace Widgets
{
    // Button
    inline bool Button(const std::string& label, const ImVec2& size = ImVec2(0, 0))
    {
        return ImGui::Button(label.c_str(), size);
    }

    // Text
    inline void Text(const std::string& text)
    {
        ImGui::Text("%s", text.c_str());
    }

    // Text Field (Input Text)
    inline bool InputText(const std::string& label, std::string& buffer, ImGuiInputTextFlags flags = 0)
    {
        char tempBuffer[256];
        strncpy(tempBuffer, buffer.c_str(), sizeof(tempBuffer));
        tempBuffer[sizeof(tempBuffer) - 1] = '\0';
        bool result = ImGui::InputText(label.c_str(), tempBuffer, sizeof(tempBuffer), flags);
        if (result)
        {
            buffer = tempBuffer;
        }
        return result;
    }

    // Menu
    inline bool BeginMenu(const std::string& label, bool enabled = true)
    {
        return ImGui::BeginMenu(label.c_str(), enabled);
    }

    inline void EndMenu()
    {
        ImGui::EndMenu();
    }

    // Popup
    inline void OpenPopup(const std::string& popupId)
    {
        ImGui::OpenPopup(popupId.c_str());
    }

    inline bool BeginPopup(const std::string& popupId, ImGuiWindowFlags flags = 0)
    {
        return ImGui::BeginPopup(popupId.c_str(), flags);
    }

    inline void EndPopup()
    {
        ImGui::EndPopup();
    }

    // Popup Modal
    inline bool BeginPopupModal(const std::string& name, bool* open = nullptr, ImGuiWindowFlags flags = 0)
    {
        return ImGui::BeginPopupModal(name.c_str(), open, flags);
    }

    inline void CloseCurrentPopup()
    {
        ImGui::CloseCurrentPopup();
    }

    // Window
    inline bool BeginWindow(const std::string& name, bool* open = nullptr, ImGuiWindowFlags flags = 0)
    {
        return ImGui::Begin(name.c_str(), open, flags);
    }

    inline void EndWindow()
    {
        ImGui::End();
    }
}