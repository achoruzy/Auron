// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "Source/Core/Window.h"

namespace Auron {
    class WinWindow: public Window
    {
    private:
        WindowSettings* Settings;
    public:
        WinWindow(WindowSettings* settings);
        ~WinWindow();
        virtual bool Initialize() override;
    };
}