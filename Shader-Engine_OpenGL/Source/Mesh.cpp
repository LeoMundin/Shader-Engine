#include "Mesh.h"

Mesh::Mesh(std ::vector<Vert> vertices, std::vector<unsigned int> indices, std::vector<Tex> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    SetUpMesh(); // This has to run, otherwise nothing loads. Note : DO NOT TOUCH!!

}

void Mesh::SetUpMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vert), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
        &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)offsetof(Vert, Normal)); // OffsetOf get the correct indent for  each value
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)offsetof(Vert, TexCoords));

    glBindVertexArray(0);
}

void Mesh::Draw(Shader& shader){
    unsigned int diffuseIndex = 1;
    unsigned int specularIndex = 1;

    for (unsigned int i = 0; i < textures.size(); i++){
        std::string textureIndex;
        std::string textureType = textures[i].type;

        // TODO : This could probabaly be a struct for future textures
        if (textureType == "texture_diffuse")
            textureIndex = std::to_string(diffuseIndex++);
        else if (textureType == "texture_specular")
            textureIndex = std::to_string(specularIndex++);

        // Update the shader uniform for this texture, given the values above
        // NOTE : The addition of "material." is dependant on whether textures are passed to structs in the shader
        shader.setInt((textureType + textureIndex).c_str(), i); 



        // Activate and bind the correct texture unit
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    // draw mesh 
    // TODO : Abstract
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
