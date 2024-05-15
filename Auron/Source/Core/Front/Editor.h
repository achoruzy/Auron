// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

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

    public:
        Editor();
        ~Editor();
        static Editor& Get() { return *single_Instance; }

        int Initialize(Window* ActiveWindow);
        void Update();
    };
}