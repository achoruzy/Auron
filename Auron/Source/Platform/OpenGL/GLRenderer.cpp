// Copyright (C) Auron Project by Arkadiusz Choruzy
// All rights reserved.

#define GLFW_INCLUDE_NONE
#include "GLRenderer.h"
#include "Source/Core/Logger.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Auron {
    GLRenderer::GLRenderer()
    {
    }

    GLRenderer::~GLRenderer()
    {
    }

    void GLRenderer::Initialize()
    {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            LOG_CRITICAL("OpenGL context couldn't be initialized.");
        }
        LOG_INFO("Initialized OpenGL ver. {0}.{1}", GLVersion.major, GLVersion.minor);
    }

    /// @brief  Per frame rendering pipeline. To be called in main loop.
    void GLRenderer::Update()
    {
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        // EXPERIMENTS =================================================
        
        // DATA ============
        float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left 
        };
        unsigned int indices[] = {
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };  

        // VERTEX BUFFER OBJECT ========
        // create vertex buffer objects (may be many)
        const int vboCount = 1;
        GLuint VBO[vboCount];
        glGenBuffers(vboCount, VBO);
        // bind buffer to actual array (vertex) buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); // may be bind only one buffer at a time
        // copy vertex data into array buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // use GL_DYNAMIC_DRAW for optimising movable objects

        // SHADERS ===========
        const char *vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main() { gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); }\0";
        
        GLuint vertShader;
        vertShader = glCreateShader(GL_VERTEX_SHADER); // creating some shader object of given type
        glShaderSource(vertShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertShader);

        // shader compilation debug
        
        int  success;
        char infoLog[512];
        glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
            LOG_ERROR("Vertex shader compilation failed: %s", infoLog);
        }

        // fragment
        const char *fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main() { FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); } \0";
        
        GLuint fragShader;
        fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragShader);

        int  successFrag;
        char infoLogFrag[512];
        glGetShaderiv(vertShader, GL_COMPILE_STATUS, &successFrag);
        if(!successFrag)
        {
            glGetShaderInfoLog(fragShader, 512, NULL, infoLogFrag);
            LOG_ERROR("Fragment shader compilation failed: %s", infoLogFrag);
        }

        // shader program ========
        GLuint shaderProgram;
        shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, vertShader);
        glAttachShader(shaderProgram, fragShader);
        glLinkProgram(shaderProgram); // if linked right the result is proper shader program

        int  successLink;
        char infoLogLink[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successLink);
        if(!successLink) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLogLink);
            LOG_ERROR("Shader program linking failed: %s", infoLogLink);
        }


        // shader objects are not needed after linking into program
        glDeleteShader(vertShader);
        glDeleteShader(fragShader);

        // VERTEX ARRAY OBJECT ========
        // VAO is an array of pointers to 
        GLuint VAO;
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO); // binding VAO objects to GPU vertex array
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); // binding VBO data to VAO
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // DATA -> SHADER PROGRAM transition =======
        // as we have our shader program, now it should get some data
        // it is done with vertex attribute pointer and enabling it - one per one set of data
        // data is taken from currently binded VAO or VBO (if no VAO)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0); // vertex data
        glEnableVertexAttribArray(0);

        // ELEMENT BUFFER OBJECT =====
        GLuint EBO;
        glGenBuffers(1, &EBO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        // RENDERER ============
        glUseProgram(shaderProgram); // shader program may be now used - this is rendering call
        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // settings for polygon drawing; may be GL_FILL
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    
    void GLRenderer::UpdateViewport(const int w, const int h) const
    {
        glViewport(0, 0, w, h);
    }
}