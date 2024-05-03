// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include <string>


namespace Auron {
    struct WindowSettings
    {
        int Width;
        int Height;
        std::string Title;

        // default
        WindowSettings():
            Width(1080), Height(768), Title("Auron Engine") {}
    };
}