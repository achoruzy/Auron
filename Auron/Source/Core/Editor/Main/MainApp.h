// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

namespace Auron {

    class MainApp
    {
    private:
        static MainApp* single_Instance;

    public:
        MainApp();
        ~MainApp();
        static MainApp& Get() { return *single_Instance; }
        int Start();
    };
}