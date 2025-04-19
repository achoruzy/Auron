#pragma once

// #include "Initial.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// #include "openio.

namespace Auron {

    class SplashScreen {
    private:
        float fadeSpeed;
        float elapsedTime;
        bool isSplashActive;
        float alpha;
        ImGuiContext* m_ImGuiContext; // Declare the ImGui context
        void ShowSplashScreen();
        
        public:
        SplashScreen() : fadeSpeed(1.0f), elapsedTime(0.0f), isSplashActive(true), alpha(0.0f) {}
        ~SplashScreen();
        int Run();
        bool IsSplashActive() const { return isSplashActive; }
        void SetFadeSpeed(float speed) { fadeSpeed = speed; }
    };
}