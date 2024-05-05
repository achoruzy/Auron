// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "Source/Core/Input.h"
#include <GLFW/glfw3.h>

namespace Auron {
    class WinInput: public Input
    {
    private:
    public:
        virtual void Poll() override;
        virtual void OnKeyCallback(const int key, const int scancode, const int action, const int mods) override;
        virtual void OnMouseButtonCallback(const int button, const int action, const int mods) override;
        virtual void OnCursorCallback(const double xpos, const double ypos) override;
    };
}