#include "Header/VAO.h"

VAO::VAO() 
{

    // Create a Vertex Array Object to inform the GPU how to interpret the currently bound Vertex Buffer.
    glGenVertexArrays(1, &ID);
    Bind();

}

void VAO::LinkVBOAttributes(VBO vbo) {
    vbo.Bind();
    Bind();

    // Configure the vertex attribute pointers for our current vertex buffer
    // 
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture Attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
}

void VAO::LinkEBO(EBO ebo){
    Bind();
    ebo.Bind();  // Bind Element Buffer so that it is stored withing the VAO.

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