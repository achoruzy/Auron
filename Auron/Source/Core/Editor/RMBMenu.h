#pragma once

#include "imgui.h"
#include <functional>
#include <unordered_map>
#include <string>
#include <iostream>


class RMBMenu {
public:
    using MenuCallback = std::function<void()>;

    void RegisterMenuOption(const std::string& objectID, const std::string& optionName, MenuCallback callback) {
        menuOptions[objectID][optionName] = callback;
    }

    void ShowMenu(const std::string& objectID) {
        if (menuOptions.find(objectID) == menuOptions.end()) {
            return; // No menu options for this object
        }

        if (ImGui::BeginPopupContextItem("RMBMenu")) {
            for (const auto& [optionName, callback] : menuOptions[objectID]) {
                if (ImGui::MenuItem(optionName.c_str())) {
                    callback();
                }
            }
            ImGui::EndPopup();
        }
    }

    void HandleRightClick(const std::string& objectID) {
        // if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
            ImGui::OpenPopup("RMBMenu");
            ShowMenu(objectID);
        // }
    }

private:
    std::unordered_map<std::string, std::unordered_map<std::string, MenuCallback>> menuOptions;
};