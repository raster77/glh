#ifndef ASSIMPIMPORTER_HPP
#define ASSIMPIMPORTER_HPP

#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>

namespace glh
{

class AssimpImporter
{
public:

    struct Vertex {
        // position
        glm::vec3 Position;
        // normal
        glm::vec3 Normal;
        // texCoords
        glm::vec2 TexCoords;
        // tangent
        glm::vec3 Tangent;
        // bitangent
        glm::vec3 Bitangent;
    };

    AssimpImporter();
    ~AssimpImporter();

    void loadModel(const std::string& path);
    const std::vector<std::pair<std::vector<glh::AssimpImporter::Vertex>, std::vector<unsigned int>>>& getDatas()
    {
        return meshes;
    }
    
    std::vector<float> getDatasAsVNU();


private:
    void processNode(aiNode *node, const aiScene *scene);
    std::vector<std::pair<std::vector<glh::AssimpImporter::Vertex>, std::vector<unsigned int>>> meshes;
    std::pair<std::vector<glh::AssimpImporter::Vertex>, std::vector<unsigned int>> processMesh(aiMesh *mesh, const aiScene *scene);

};

}

#endif // ASSIMPIMPORTER_HPP
