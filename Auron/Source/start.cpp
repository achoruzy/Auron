// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "Core/Auron.h"
#include "Core/Editor/Main/MainApp.h"
#include "Core/Event/Event.h"
#include "Core/Logger.h"
#include <iostream>


int main(int argc, char** argv)
{
    // auto auron = Auron::Auron();
    // auron.Initialize();
    // auron.Run();

    Auron::Logger::Initialize();

    auto auron = Auron::MainApp();
    auron.Start();


    return 0;
}