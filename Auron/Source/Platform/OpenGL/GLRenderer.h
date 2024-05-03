// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "Source/Core/Renderer.h"
#include <GLFW/glfw3.h>

namespace Auron {
    class GLRenderer: public Renderer
    {
    private:
    public:
        virtual void Initialize() override;
        virtual void Update() override;
    };
}