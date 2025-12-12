#pragma once
#ifndef VAO_H
#define VAO_H

#include "VBO.h"
#include "EBO.h"


class VAO
{
public:

    unsigned int ID;
    VAO();

    void LinkVBOAttributes(VBO vbo);
    void LinkEBO(EBO ebo);
    void Bind();
    void Unbind();
};


#endif