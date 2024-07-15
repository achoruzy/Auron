// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "SceneObject.h"
#include <vector>

namespace Auron { 

    class Scene
    {
    private:
        std::vector<SceneObject*> SceneObjects;
    public:
        Scene();
        ~Scene();
        void AddObject();
        bool RemoveObject(int id);
        std::vector<SceneObject*> GetObjects();

    };
}