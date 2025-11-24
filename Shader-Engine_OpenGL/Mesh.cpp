#include "Mesh.h"

Mesh::Mesh(std ::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    //setupMesh();
}

void Mesh::SetUpMesh()
{

    // Create + bind, VBO, EBO, VAO
    VAO vao = new VAO();
    VBO vbo = new VBO();
    EBO ebo = new EBO();

    vao.LinkVBOAttributes();
    vao.linkEBO();

    vao.Unbind();

}