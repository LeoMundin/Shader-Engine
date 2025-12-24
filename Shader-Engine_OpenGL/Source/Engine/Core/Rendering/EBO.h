#pragma once
#ifndef EBO_H
#define EBO_H


#include <glad.h> 
#include <glfw3.h>


class EBO
{
public:

    unsigned int ID;

    // Passes a pointer to the data as well as the size of that data, this prevents array decay.
    EBO(float* indicies, GLsizeiptr size);

    void Bind();
    void Unbind();

};


#endif