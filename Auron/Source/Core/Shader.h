// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include <string>


namespace Auron { 
    class Shader
    {
    public:
        void LoadFromFile();
        void LoadFromString();
        virtual void CreateProgram() = 0;
        virtual void Use() = 0;
        virtual void StopUsing() = 0;
        virtual void AddAttribute(const std::string& attribute) = 0;
        virtual void AddUniform(const std::string& uniform) = 0;
        virtual void DeleteProgram() = 0;
    };
}