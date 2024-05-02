// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "WinInput.h"
#include <GLFW/glfw3.h>


void Auron::WinInput::Poll()
{
    glfwPollEvents();
}