#pragma once
#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "stb_image.h" // Image loading capabilites


class Model
{
public:
    Model(const char* path)
    {
        loadModel(path);
    }

    void Draw(Shader& shader);

private:
    // model data
    std::vector<Tex> textures_loaded;// Saves on loading existing textures.
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    // Helper Functions.
    std::vector<Tex> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

    // TODO : Replace with own implementation from Texture Class.
    unsigned int TextureFromFile(const char* path, const std::string& directory);
};

#endif