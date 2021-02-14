#include "AssimpImporter.hpp"
#include <iostream>

glh::AssimpImporter::AssimpImporter()
{
}

glh::AssimpImporter::~AssimpImporter()
{
}

void glh::AssimpImporter::loadModel(const std::string& path)
{
    // read file via ASSIMP
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) { // if is Not Zero
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    // retrieve the directory path of the filepath
    std::string directory = path.substr(0, path.find_last_of('/'));

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);

}

void glh::AssimpImporter::processNode(aiNode *node, const aiScene *scene)
{
    // process each mesh located at the current node
    for(std::size_t i = 0; i < node->mNumMeshes; i++) {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

std::pair<std::vector<glh::AssimpImporter::Vertex>, std::vector<unsigned int>> glh::AssimpImporter::processMesh(aiMesh *mesh, const aiScene *scene)
{
    // data to fill
    std::pair<std::vector<glh::AssimpImporter::Vertex>, std::vector<unsigned int>> datas;

    // Walk through each of the mesh's vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        // texture coordinates
        if(mesh->mTextureCoords[0]) { // does the mesh contain texture coordinates?
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        } else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        // tangent
        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.Tangent = vector;
        // bitangent
        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.Bitangent = vector;
        datas.first.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            datas.second.push_back(face.mIndices[j]);
    }

    // return a mesh object created from the extracted mesh data
    return datas;
}

std::vector<float> glh::AssimpImporter::getDatasAsVNU()
{
    std::vector<float> vertices;
    
    for(auto& m : meshes) {
        for(auto& v : m.first) {
            vertices.emplace_back(v.Position.x);
            vertices.emplace_back(v.Position.y);
            vertices.emplace_back(v.Position.z);
            vertices.emplace_back(v.Normal.x);
            vertices.emplace_back(v.Normal.y);
            vertices.emplace_back(v.Normal.z);
            vertices.emplace_back(v.TexCoords.x);
            vertices.emplace_back(v.TexCoords.y);
        }
    }
    return vertices;
}
