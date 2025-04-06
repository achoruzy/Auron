// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "CommandConsole.h"
#include <vector>
#include <glm/glm.hpp>

struct ImGuiContext;
struct ImGuiIO;

namespace Auron {
    class Window;

    class Editor
    {
    private:
        static Editor* single_Instance;
        ImGuiContext* m_ImGuiContext;
        ImGuiIO* m_ImGuiIO;
        CommandConsole* m_CommandConsole;

        // Line drawing
        struct Line {
            glm::vec2 start;
            glm::vec2 end;
            ImVec4 color;
        };
        std::vector<Line> m_lines;
        bool m_isDrawingLine;
        glm::vec2 m_currentLineStart;
        ImVec4 m_currentLineColor;

    public:
        Editor();
        ~Editor();
        static Editor& Get() { return *single_Instance; }

        int Initialize(Window* ActiveWindow);
        void Update();
        void HandleRightClickMenu();
        void HandleLineDrawing();
        void ClearLines();
    };
}