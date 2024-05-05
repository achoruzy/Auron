// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once


namespace Auron {
    class Input
    {
    public:
        virtual void Poll() = 0;
        virtual void OnKeyCallback(const int key, const int scancode, const int action, const int mods) = 0;
        virtual void OnMouseButtonCallback(const int button, const int action, const int mods) = 0;
        virtual void OnCursorCallback(const double xpos, const double ypos) = 0;
    };
}