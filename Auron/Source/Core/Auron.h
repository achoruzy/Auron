// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

namespace Auron {
    /// @brief Base engine initialization and work class.
    class Auron
    {
    public:
        Auron();
        ~Auron();
        static Auron& Get() { return *single_Instance; }

        int Initialize();
    
    private:
        static Auron* single_Instance;
    };
}