// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#include "Auron.h"
#include "Logger.h"


namespace Auron {

    Auron* Auron::single_Instance = nullptr;

    Auron::Auron()
    {
        if (single_Instance != nullptr)
        {
            single_Instance = this;
        }
    }

    Auron::~Auron()
    {
    }

    int Auron::Initialize()
    {
        Logger::Initialize();
        return 0;
    }
}