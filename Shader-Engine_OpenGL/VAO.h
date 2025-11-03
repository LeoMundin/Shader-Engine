#pragma once
#ifndef VAO_H
#define VAO_H


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


#endif