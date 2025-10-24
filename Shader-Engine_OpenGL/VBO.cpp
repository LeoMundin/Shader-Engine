#include "VBO.h"

VBO::VBO(float* vertices, GLsizeiptr size)
{

    // Generate a vertex buffer object and bind it to the GL_ARRAY_BUFFER.
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);

    // copy vertices array in a buffer for OpenGL to use
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    // Prevents misshaps with this VBO later on.
    Unbind();

}

void VBO::Bind() {

    // binds to openGls Array Buffer where we wish to asign our data.
    glBindBuffer(GL_ARRAY_BUFFER, ID);

}

void VBO::Unbind() {

    // Unbinds this Vertex buffer;
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}



