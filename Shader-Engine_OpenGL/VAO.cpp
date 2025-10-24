#include "VAO.h"

VAO::VAO() {

    // Create a Vertex Array Object to inform the GPU how to interpret the currently bound Vertex Buffer.
    glGenVertexArrays(1, &ID);

}

void VAO::LinkVBO(VBO vbo) {

    // bind to the correct buffers
    vbo.Bind();
    Bind();

    // Configure the vertex attribute pointers for our current vertex buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind to prevent any issues down the line
    vbo.Unbind();
    Unbind();
    
}

void VAO::Bind() {

    // Bind the Vertex array we want to use. 
    // NOTE: This is usually done right before drawring and unbound straight after, to avoid interpreting the vertex buffer incorrectly.
    glBindVertexArray(ID);

}

void VAO::Unbind() {

    // Unbinds this Vertex array
    glBindVertexArray(0);

}