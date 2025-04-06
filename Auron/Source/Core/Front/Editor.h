// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "CommandConsole.h"

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

    public:
        Editor();
        ~Editor();
        static Editor& Get() { return *single_Instance; }

        int Initialize(Window* ActiveWindow);
        void Update();
        void HandleRightClickMenu();
    };
}