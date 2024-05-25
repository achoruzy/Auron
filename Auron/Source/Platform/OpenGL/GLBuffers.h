// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#pragma once

#include <map>
#include <glad/glad.h>


namespace Auron { 
    class SceneObject;
    class Shader;

    class GLBuffer
    {
    // TODO: rework for one buffer object per shader and list of buffers separately
    private:
        std::map<Shader*, GLuint> VBOs;
        std::map<Shader*, GLuint> VAOs;
        std::map<Shader*, GLuint> EBOs;

    public:
        GLBuffer();
        ~GLBuffer();
        void Initialize();
        void DrawObject(SceneObject* object);
        // void DrawCanvas(); // screen postprocess
    
    private:
        void SetOrGenerateBuffers(Shader* shader);
    };
}