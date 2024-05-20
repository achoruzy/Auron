// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "Source/Core/Logger.h"
#include "Source/Core/Shader.h"
#include "Source/Core/Scene/SceneObject.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>


namespace Auron { 
    class GLBuffers
    {
    // TODO: rework for one buffer object per shader and list of buffers separately
    private:
        std::map<Shader*, GLuint> VBOs;
        std::map<Shader*, GLuint> VAOs;
        std::map<Shader*, GLuint> EBOs;

    public:
        GLBuffers();
        ~GLBuffers();
        void DrawObject(SceneObject* object);
        // void DrawCanvas(); // screen postprocess
    
    private:
        void SetOrGenerateBuffers(Shader* shader);
    };
}