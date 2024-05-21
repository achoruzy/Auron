// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "Source/Core/Renderer.h"


namespace Auron {
    class GLRenderer: public Renderer
    {
    public:
        GLRenderer();
        ~GLRenderer();
        virtual void Initialize() override;
        virtual void Update() override;
        virtual void UpdateViewport(const int w, const int h) const override;
    };
}