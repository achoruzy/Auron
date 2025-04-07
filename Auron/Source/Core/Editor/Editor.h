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
            bool isSelected;
        };
        std::vector<Line> m_lines;
        bool m_isDrawingLine;
        glm::vec2 m_currentLineStart;
        ImVec4 m_currentLineColor;
        const float SNAP_DISTANCE = 5.0f;
        const float HIGHLIGHT_DISTANCE = 5.0f;
        int m_selectedLineIndex;
        glm::vec2 m_hoveredPoint;
        bool m_isPointHovered;
        int m_hoveredLineIndex;
        bool m_isLineHovered;

        // Helper methods
        glm::vec2 FindNearestPoint(const glm::vec2& point);
        bool IsPointNearLine(const glm::vec2& point, const Line& line);
        float DistanceToLine(const glm::vec2& point, const glm::vec2& lineStart, const glm::vec2& lineEnd);
        void DrawPoint(const glm::vec2& point, const ImVec4& color, float radius = 3.0f);
        void DrawLineHighlight(const Line& line, const ImVec4& color);

    public:
        Editor();
        ~Editor();
        static Editor& Get() { return *single_Instance; }

        int Initialize(Window* ActiveWindow);
        void Update();
        void HandleRightClickMenu();
        void HandleLineDrawing();
        void ClearLines();
        void DeleteSelectedLine();
    };
}