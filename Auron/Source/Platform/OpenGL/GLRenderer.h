// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "Source/Core/Renderer.h"
#include "Source/Core/WindowSettings.h"
#include <GLFW/glfw3.h>

namespace Auron {
    class GLRenderer: public Renderer
    {
    private:
        GLFWwindow* m_Window;
    public:
        GLRenderer(GLFWwindow* window);
        ~GLRenderer();
        virtual void Initialize() override;
        virtual void Update() override;
        virtual void UpdateViewport(int x, int y, int w, int h) override;
    };
}