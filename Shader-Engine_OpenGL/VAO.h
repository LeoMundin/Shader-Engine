#pragma once

#include "VBO.h"

class VAO
{
public:

    unsigned int ID;
    VAO();

    void LinkVBO(VBO vbo);
    void Bind();
    void Unbind();
};
