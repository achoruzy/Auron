// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include "Source/Core/RenderBuffer.h"
#include <map>
#include <glad/glad.h>


namespace Auron { 
    class SceneObject;
    class Shader;

    class GLBuffer : RenderBuffer
    {
    // TODO: rework for one buffer object per shader and list of buffers separately
    private:
        std::map<Shader*, GLuint> VBOs;
        std::map<Shader*, GLuint> VAOs;
        std::map<Shader*, GLuint> EBOs;
        SceneObject* object;
        Shader* shader;

    public:
        GLBuffer(SceneObject* object, Shader* shader);
        ~GLBuffer();
        virtual void DrawObject() override;
    
    private:
        void Initialize();
        void SetOrGenerateBuffers();
    };
}