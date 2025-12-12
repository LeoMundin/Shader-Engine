#pragma once
#ifndef VBO_H
#define VBO_H


#include <glad.h> 
#include <glfw3.h>


class VBO
{
public:

    unsigned int ID;

    // Passes a pointer to the data as well as the size of that data, this prevents array decay.
    VBO(float* vertices, GLsizeiptr size);

    void Bind();
    void Unbind();

};


#endif