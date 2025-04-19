// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.


#include "Splash.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>


namespace Auron {



    SplashScreen::~SplashScreen()
    {
        // Cleanup ImGui context if needed
        if (m_ImGuiContext) {
            ImGui::DestroyContext(m_ImGuiContext);
        }
        // Cleanup other resources if needed
    }

    int SplashScreen::Run() {
        if (!glfwInit()) {
            return -1;
        }

        // Defining a monitor
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        // Create a GLFW window
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        GLFWwindow* window = glfwCreateWindow(800, 480, "Splash Screen Example", nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync
        
        // Putting it in the centre
        glfwSetWindowPos(window, (mode->width - 800)/2, (mode->height - 480)/2);

        // Initialize OpenGL loader (e.g., glad, glew, etc.)
        // Make sure to include your OpenGL loader initialization here

        // Initialize ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGui::StyleColorsDark();

        // Initialize ImGui backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");

        // Main loop
        while (!glfwWindowShouldClose(window)) {
            // Poll events
            glfwPollEvents();

            // Start ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // Render splash screen or initial window

            ShowSplashScreen();

            // Render ImGui
            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Swap buffers
            glfwSwapBuffers(window);

            if (IsSplashActive() == false) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
        }

        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();

        return 0;
    }

    void SplashScreen::ShowSplashScreen() {

        ImGui::SetNextWindowSize(ImVec2(800, 480));
        ImGui::SetNextWindowPos(ImVec2((ImGui::GetIO().DisplaySize.x - 800) / 2,
                                    (ImGui::GetIO().DisplaySize.y - 480) / 2));
        ImGui::SetNextWindowBgAlpha(alpha);

        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar |
                                    ImGuiWindowFlags_NoResize |
                                    ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoScrollbar |
                                    ImGuiWindowFlags_NoCollapse |
                                    ImGuiWindowFlags_NoDecoration |
                                    ImGuiWindowFlags_NoSavedSettings;

        ImGui::Begin("Splash Screen", nullptr, windowFlags);

        // Background image
        ImGui::SetCursorPos(ImVec2(0, 0));
        // ImGui::Image((void*)(intptr_t)LoadTexture("Auron\\Assets\\splash.jpg"), ImVec2(800, 600));

        // Loading text with percentage
        ImGui::SetCursorPos(ImVec2(10, 480-20));
        int percent = static_cast<int>((elapsedTime / 3.0f) * 100.0f);
        percent = percent > 100 ? 100 : percent;
        ImGui::Text("Loading... %d%%", percent);

        ImGui::End();

        // Update fade animation and elapsed time
        elapsedTime += ImGui::GetIO().DeltaTime;
        if (elapsedTime < 1.5f) {
            alpha += fadeSpeed * ImGui::GetIO().DeltaTime;
            if (alpha > 1.0f) alpha = 1.0f;
        } else if (elapsedTime > 1.5f && elapsedTime < 3.0f) {
            alpha -= fadeSpeed * ImGui::GetIO().DeltaTime;
            if (alpha < 0.0f) alpha = 0.0f;
        } else {
            isSplashActive = false;
        }

        if (elapsedTime > 3.0f) {
        }
    }



// Dummy texture loader (replace with your actual texture loading function)
// void* LoadTexture(const char* path) {
//     // Implement your texture loading logic here
//     return nullptr;
// }
};