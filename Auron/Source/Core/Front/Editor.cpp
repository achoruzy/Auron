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
#include <algorithm>

namespace Auron {

    Editor* Editor::single_Instance = nullptr;

    Editor::Editor()
        : m_isDrawingLine(false)
        , m_currentLineColor(1.0f, 1.0f, 1.0f, 1.0f)
        , m_selectedLineIndex(-1)
        , m_isPointHovered(false)
        , m_hoveredLineIndex(-1)
        , m_isLineHovered(false)
        , m_cameraPosition(0.0f, 0.0f)
        , m_cameraRotation(0.0f)
        , m_cameraZoom(1.0f)
        , m_isRotatingCamera(false)
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

        HandleCameraRotation();
        HandleLineDrawing();
        m_CommandConsole->Draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    glm::vec2 Editor::FindNearestPoint(const glm::vec2& point)
    {
        glm::vec2 nearestPoint = point;
        float minDistance = SNAP_DISTANCE;

        for (const auto& line : m_lines) {
            float distToStart = glm::distance(point, line.start);
            float distToEnd = glm::distance(point, line.end);

            if (distToStart < minDistance) {
                minDistance = distToStart;
                nearestPoint = line.start;
            }
            if (distToEnd < minDistance) {
                minDistance = distToEnd;
                nearestPoint = line.end;
            }
        }

        return (minDistance < SNAP_DISTANCE) ? nearestPoint : point;
    }

    bool Editor::IsPointNearLine(const glm::vec2& point, const Line& line)
    {
        return DistanceToLine(point, line.start, line.end) < HIGHLIGHT_DISTANCE;
    }

    float Editor::DistanceToLine(const glm::vec2& point, const glm::vec2& lineStart, const glm::vec2& lineEnd)
    {
        glm::vec2 line = lineEnd - lineStart;
        float lineLength = glm::length(line);
        if (lineLength < 0.0001f) return glm::distance(point, lineStart);

        glm::vec2 normalizedLine = line / lineLength;
        glm::vec2 pointToStart = point - lineStart;
        float projection = glm::dot(pointToStart, normalizedLine);

        if (projection < 0) return glm::distance(point, lineStart);
        if (projection > lineLength) return glm::distance(point, lineEnd);

        glm::vec2 projectedPoint = lineStart + normalizedLine * projection;
        return glm::distance(point, projectedPoint);
    }

    void Editor::DrawPoint(const glm::vec2& point, const ImVec4& color, float radius)
    {
        ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
        draw_list->AddCircleFilled(ImVec2(point.x, point.y), radius, ImColor(color));
    }

    void Editor::DrawLineHighlight(const Line& line, const ImVec4& color)
    {
        ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
        draw_list->AddLine(
            ImVec2(line.start.x, line.start.y),
            ImVec2(line.end.x, line.end.y),
            ImColor(color),
            4.0f
        );
    }

    glm::vec2 Editor::ScreenToWorld(const glm::vec2& screenPos)
    {
        // Get window size
        ImVec2 windowSize = ImGui::GetIO().DisplaySize;
        glm::vec2 center(windowSize.x * 0.5f, windowSize.y * 0.5f);

        // Translate to center
        glm::vec2 pos = screenPos - center;

        // Apply zoom
        pos /= m_cameraZoom;

        // Apply rotation
        float cosRot = cos(-m_cameraRotation);
        float sinRot = sin(-m_cameraRotation);
        glm::vec2 rotatedPos(
            pos.x * cosRot - pos.y * sinRot,
            pos.x * sinRot + pos.y * cosRot
        );

        // Translate back and add camera position
        return rotatedPos + m_cameraPosition;
    }

    glm::vec2 Editor::WorldToScreen(const glm::vec2& worldPos)
    {
        // Get window size
        ImVec2 windowSize = ImGui::GetIO().DisplaySize;
        glm::vec2 center(windowSize.x * 0.5f, windowSize.y * 0.5f);

        // Subtract camera position
        glm::vec2 pos = worldPos - m_cameraPosition;

        // Apply rotation
        float cosRot = cos(m_cameraRotation);
        float sinRot = sin(m_cameraRotation);
        glm::vec2 rotatedPos(
            pos.x * cosRot - pos.y * sinRot,
            pos.x * sinRot + pos.y * cosRot
        );

        // Apply zoom
        rotatedPos *= m_cameraZoom;

        // Translate to screen coordinates
        return rotatedPos + center;
    }

    void Editor::HandleCameraRotation()
    {
        // Skip if mouse is over any ImGui window or item
        if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) || ImGui::IsAnyItemHovered()) {
            return;
        }

        glm::vec2 currentMousePos = glm::vec2(ImGui::GetMousePos().x, ImGui::GetMousePos().y);

        if (ImGui::IsMouseDown(ImGuiMouseButton_Middle)) {
            if (!m_isRotatingCamera) {
                m_isRotatingCamera = true;
                m_lastMousePos = currentMousePos;
            } else {
                // Calculate rotation based on mouse movement
                glm::vec2 delta = currentMousePos - m_lastMousePos;
                m_cameraRotation += delta.x * 0.01f; // Adjust sensitivity as needed
                m_lastMousePos = currentMousePos;
            }
        } else {
            m_isRotatingCamera = false;
        }
    }

    void Editor::HandleLineDrawing()
    {
        // Skip line drawing if mouse is over any ImGui window or item
        if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) || ImGui::IsAnyItemHovered()) {
            return;
        }

        ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
        glm::vec2 mousePos = ScreenToWorld(glm::vec2(ImGui::GetMousePos().x, ImGui::GetMousePos().y));
        
        // Check for line hover
        m_isLineHovered = false;
        m_hoveredLineIndex = -1;
        for (size_t i = 0; i < m_lines.size(); ++i) {
            if (IsPointNearLine(mousePos, m_lines[i])) {
                m_isLineHovered = true;
                m_hoveredLineIndex = static_cast<int>(i);
                break;
            }
        }

        // Check for point hover
        m_isPointHovered = false;
        for (const auto& line : m_lines) {
            if (glm::distance(mousePos, line.start) < HIGHLIGHT_DISTANCE) {
                m_isPointHovered = true;
                m_hoveredPoint = line.start;
                break;
            }
            if (glm::distance(mousePos, line.end) < HIGHLIGHT_DISTANCE) {
                m_isPointHovered = true;
                m_hoveredPoint = line.end;
                break;
            }
        }

        // Draw existing lines
        for (size_t i = 0; i < m_lines.size(); ++i) {
            const auto& line = m_lines[i];
            ImVec4 lineColor = line.color;
            if (i == m_selectedLineIndex) {
                lineColor = ImVec4(1.0f, 1.0f, 0.0f, 1.0f); // Yellow for selected
            } else if (i == m_hoveredLineIndex) {
                lineColor = ImVec4(0.0f, 1.0f, 1.0f, 1.0f); // Cyan for hovered
            }
            
            // Convert world coordinates to screen coordinates for drawing
            glm::vec2 screenStart = WorldToScreen(line.start);
            glm::vec2 screenEnd = WorldToScreen(line.end);
            
            draw_list->AddLine(
                ImVec2(screenStart.x, screenStart.y),
                ImVec2(screenEnd.x, screenEnd.y),
                ImColor(lineColor),
                2.0f
            );

            // Draw points
            DrawPoint(screenStart, lineColor);
            DrawPoint(screenEnd, lineColor);
        }

        // Draw hovered point
        if (m_isPointHovered) {
            glm::vec2 screenPoint = WorldToScreen(m_hoveredPoint);
            DrawPoint(screenPoint, ImVec4(1.0f, 0.0f, 0.0f, 1.0f), 4.0f);
        }

        // Handle line drawing
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            if (!m_isDrawingLine) {
                // Start new line
                m_isDrawingLine = true;
                m_currentLineStart = FindNearestPoint(mousePos);
            } else {
                // Complete the line
                m_isDrawingLine = false;
                glm::vec2 end = FindNearestPoint(mousePos);
                m_lines.push_back({m_currentLineStart, end, m_currentLineColor, false});
            }
        }

        // Handle line selection
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !m_isDrawingLine && m_isLineHovered) {
            m_selectedLineIndex = m_hoveredLineIndex;
        }

        // Draw current line being drawn
        if (m_isDrawingLine) {
            glm::vec2 current = FindNearestPoint(mousePos);
            glm::vec2 screenStart = WorldToScreen(m_currentLineStart);
            glm::vec2 screenEnd = WorldToScreen(current);
            
            draw_list->AddLine(
                ImVec2(screenStart.x, screenStart.y),
                ImVec2(screenEnd.x, screenEnd.y),
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

    void Editor::DeleteSelectedLine()
    {
        if (m_selectedLineIndex >= 0 && m_selectedLineIndex < static_cast<int>(m_lines.size())) {
            m_lines.erase(m_lines.begin() + m_selectedLineIndex);
            m_selectedLineIndex = -1;
        }
    }
}