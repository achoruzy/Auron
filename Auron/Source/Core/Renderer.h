// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

namespace Auron {
    class Renderer
    {
    public:
        virtual void Initialize() = 0;
        virtual void Update() = 0;
        virtual void UpdateViewport(const int w, const int h) const = 0;
    };
}