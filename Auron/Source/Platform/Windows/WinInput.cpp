// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "WinInput.h"
#include <GLFW/glfw3.h>
#include "Source/Core/Logger.h"


void Auron::WinInput::Poll()
{
    glfwPollEvents();
}

void Auron::WinInput::OnKeyCallback(const int key, const int scancode, const int action, const int mods)
{
    LOG_INFO("Key: {0} {1} {2} {3}", key, scancode, action, mods);
}

void Auron::WinInput::OnCursorCallback(const double xpos, const double ypos)
{
    LOG_INFO("Cursor: {0} {1}", xpos, ypos);
}

void Auron::WinInput::OnMouseButtonCallback(const int button, const int action, const int mods)
{
    LOG_INFO("Mouse Button: {0} {1} {2}", button, action, mods);
}

