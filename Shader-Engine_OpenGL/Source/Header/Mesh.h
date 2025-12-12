#pragma once
#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include "VAO.h"
#include "Shader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


struct Vert {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Tex {
    unsigned int id;
    std::string type;
    std::string path;  // we store the path of the texture to compare with other textures
};

class Mesh {
public:
    // mesh data
    std:: vector<Vert>       vertices;
    std:: vector<unsigned int> indices;
    std::vector<Tex>      textures;

    Mesh(std::vector<Vert> vertices, std::vector<unsigned int> indices, std::vector<Tex> textures);
    void Draw(Shader& shader);
private:
    //  render data
    unsigned int VAO, VBO, EBO; // TODO : Replace with class.ID

    void SetUpMesh(); // TODO : Refactor to utelize classes not new versions.
};

#endif