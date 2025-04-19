// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "MainApp.h"
#include "Source/Core/Window.h"
#include "Source/Core/Renderer.h"
#include "Source/Core/Logger.h"
#include "Source/Core/WindowSettings.h"
#include "Source/Platform/OpenGL/GLRenderer.h"
#include "Source/Platform/Windows/WinWindow.h"
#include "Source/Platform/Windows/WinInput.h"
#include "Splash.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

namespace Auron {

    MainApp* MainApp::single_Instance = nullptr;

    MainApp::MainApp()
    {
        if (single_Instance != nullptr)
        {
            single_Instance = this;
        }
    }

    MainApp::~MainApp()
    {

    }

    int MainApp::Start()
    {
        LOG_INFO("Auron Ship Initiated.");
        LOG_INFO("Auron Ship version: 0.1.0");
        LOG_INFO("Auron Ship build date: " __DATE__ " " __TIME__);

        LOG_INFO("SplashScreen started.");

        SplashScreen splashScreen;
        splashScreen.SetFadeSpeed(2.f);
        splashScreen.Run();

        LOG_INFO("SplashScreen closed.");

        return 0;

        // WindowSettings WinSettings;
        // m_Renderer = new GLRenderer();
        // m_Input = new WinInput();
        // m_Window = new WinWindow(&WinSettings);
        // m_Editor = new Editor();

        ////////////////////////


        // if (!glfwInit()) {
        //     return -1;
        // }

        // // Defining a monitor
        // GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        // const GLFWvidmode* mode = glfwGetVideoMode(monitor);


        // // // Putting it in the centre
        
        // // Create a GLFW window
        // // glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        // glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        // glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);
        // glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        // GLFWwindow* window = glfwCreateWindow(800, 480, "Splash Screen Example", nullptr, nullptr);
        // if (!window) {
        //     glfwTerminate();
        //     return -1;
        // }
        // glfwMakeContextCurrent(window);
        // glfwSetWindowPos(window, (mode->width - 800)/2, (mode->height - 480)/2);
        // glfwSwapInterval(1); // Enable vsync

        // // glfwSetWindowOpacity(window, 0.5f);
    
        // // Initialize OpenGL loader (e.g., glad, glew, etc.)
        // // Make sure to include your OpenGL loader initialization here
    
        // // Initialize ImGui
        // IMGUI_CHECKVERSION();
        // ImGui::CreateContext();
        // ImGuiIO& io = ImGui::GetIO();
        // ImGui::StyleColorsDark();
    
        // // Initialize ImGui backends
        // ImGui_ImplGlfw_InitForOpenGL(window, true);
        // ImGui_ImplOpenGL3_Init("#version 130");
    
        // // Create SplashScreen instance
        // SplashScreen splashScreen;
        // splashScreen.SetFadeSpeed(1.0f);
    
        // bool showInitialWindow = false;
    
        // // Main loop
        // while (!glfwWindowShouldClose(window)) {
        //     // Poll events
        //     glfwPollEvents();
    
        //     // Start ImGui frame
        //     ImGui_ImplOpenGL3_NewFrame();
        //     ImGui_ImplGlfw_NewFrame();
        //     ImGui::NewFrame();
    
        //     // Render splash screen or initial window

        //     splashScreen.ShowSplashWindow();
        //     // } else {
        //     //     // Render initial window (dummy window for now)
        //     //     ImGui::Begin("Initial Window");
        //     //     ImGui::Text("This is the initial window.");
        //     //     ImGui::End();
        //     // }
    
        //     // Render ImGui
        //     ImGui::Render();
        //     int display_w, display_h;
        //     glfwGetFramebufferSize(window, &display_w, &display_h);
        //     glViewport(0, 0, display_w, display_h);
        //     glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        //     glClear(GL_COLOR_BUFFER_BIT);
        //     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
        //     // Swap buffers
        //     glfwSwapBuffers(window);

        //     if (splashScreen.IsSplashActive() == false) {
        //         glfwSetWindowShouldClose(window, GLFW_TRUE);
        //     }
        // }
    
        // // Cleanup
        // ImGui_ImplOpenGL3_Shutdown();
        // ImGui_ImplGlfw_Shutdown();
        // ImGui::DestroyContext();
        // glfwDestroyWindow(window);
        // glfwTerminate();
    
        // return 0;


        ////////////////

        // SplashScreen splashScreen;
        // bool showInitialWindow = true;
        // while (showInitialWindow) {
        //     splashScreen.ShowSplashWindow(showInitialWindow);
        //     // Here you can add a delay or sleep to control the speed of the splash screen
        //     // For example, using std::this_thread::sleep_for(std::chrono::milliseconds(16));
        // }
        // // Initialize the main components of the engine


        // if (m_Window->Initialize(m_Renderer, m_Input))
        // {
        //     LOG_GAME_INFO("Window initialized properly.");
        // }
        // else {
        //     LOG_CRITICAL("Window couldn't be initialized.");
        // }

        // if (m_Editor->Initialize(m_Window))
        // {
        //     LOG_GAME_INFO("Editor initialized properly.");
        // }
        // else {
        //     LOG_CRITICAL("Editor couldn't be initialized.");
        // }

        // return 0;
    }

    // Main application loop
    // void MainApp::Run()
    // {
    //     while (!m_Window->ShouldClose())
    //     {
    //         m_Input->Poll();
    //         m_Window->Update();
    //         m_Renderer->Update();
    //         m_Editor->Update();
    //     }
    // }
}