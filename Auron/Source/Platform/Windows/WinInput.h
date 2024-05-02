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
    };
}