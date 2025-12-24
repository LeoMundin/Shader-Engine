#include "EBO.h"

EBO::EBO(float* indicies, GLsizeiptr size)
{

    // Generate a vertex buffer object and bind it to the GL_ARRAY_BUFFER.
    glGenBuffers(1, &ID);
    Bind();

    // copy vertices array in a buffer for OpenGL to use
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicies, GL_STATIC_DRAW);

}

void EBO::Bind() {
    // binds to openGls Element Buffer where we wish to asign our data.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

}

void EBO::Unbind() {
    // Unbinds this Element buffer;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
