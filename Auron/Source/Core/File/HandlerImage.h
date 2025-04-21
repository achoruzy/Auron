#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class HandlerImage {
public:
    // Function to open image files of jpg and png types
    static unsigned char* OpenImageFile(const std::string& filePath, int& width, int& height, int& channels) {
        // Check file extension
        if (filePath.size() < 4) {
            throw std::invalid_argument("Invalid file path.");
        }

        std::string extension = filePath.substr(filePath.find_last_of('.') + 1);
        if (extension == "jpg" || extension == "jpeg" || extension == "png") {
            // Load the image file
            unsigned char* imageData = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
            if (imageData) {
                std::cout << "Image loaded successfully: " << filePath << std::endl;
                std::cout << "Width: " << width << ", Height: " << height << ", Channels: " << channels << std::endl;
                return imageData; // Return the image data for further use
            } else {
                throw std::runtime_error("Failed to load image: " + filePath);
            }
        } else {
            throw std::invalid_argument("Unsupported file type. Only jpg and png are allowed.");
        }
    }

    static void* LoadTextureGL(const std::string& filePath, int& width, int& height) {
        int channels = 4;
        unsigned char* imageData = OpenImageFile(filePath, width, height, channels);

        // Create an OpenGL texture for ImGui
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);

        stbi_image_free(imageData); // Free the image data after uploading to GPU

        return reinterpret_cast<void*>(static_cast<intptr_t>(textureID));
    }
};