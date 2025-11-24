#include "Model.h"

void Model::Draw(Shader& shader){
    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(shader);
}


void Model::loadModel(std::string path){
    Assimp::Importer import;
    const aiScene * scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    // Error Checking
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    // Recurssively process children
    processNode(scene->mRootNode, scene);
}


void Model :: processNode(aiNode* node, const aiScene* scene){
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}


Mesh Mesh::processMesh(aiMesh* mesh, const aiScene* scene){
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++){
        // Instantiate Vertex to store data from assimp.
        Vertex vertex;

        glm::vec3 vector;

        // Process Vertex Position Coordinates.
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
            
        // Process Vertex Normals Coordinates.
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        

        // Process Texture Coordinates, if mesh contains any.
        if (mesh->mTextureCoords[0]){
            glm::vec2 vector;

            vector.x = mesh->mTextureCoords[0][i].x;
            vector.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vector;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex); // Add to the "list" of verticies

    }

    // Process Indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i]; // Retrive current face

        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]); // Add to the "list" of indicies

    }


    // TODO: Process Materials

}

