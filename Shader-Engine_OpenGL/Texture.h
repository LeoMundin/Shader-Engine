#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include "stb_image.h" // Image loading capabilites

class Texture
{
public:
    // the texture ID
    unsigned int ID;

    // constructor reads and builds the shader
    Texture(const char* filePath, bool flipTexture = false);

    void Bind();
    void Unbind();

private:

    void ConfigureParameters();

};

#endif