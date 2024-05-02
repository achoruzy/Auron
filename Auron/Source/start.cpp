// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "Core/Auron.h"
#include "Core/Event/Event.h"
#include <iostream>


int main(int argc, char** argv)
{
    auto auron = Auron::Auron();
    auron.Initialize();
    auron.Run();

    return 0;
}