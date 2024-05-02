// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include <string>


namespace Auron {
    class Input
    {
    public:
        virtual void Poll() = 0;
    };
}