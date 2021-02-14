#include "VboIndexer.hpp"
#include <iostream>

glh::VboIndexer::VboIndexer()
    : mRecomputeNormals(false)
{
}

glh::VboIndexer::~VboIndexer()
{
}

void glh::VboIndexer::process(const std::vector<float>& vertices,
    const std::vector<float>& uvs,
    const std::vector<float>& normals,
    std::vector<unsigned int>& outIndices,
    std::vector<float>& outVertices,
    std::vector<float>& outUvs,
    std::vector<float>& outNormals)
{
    // Reserve some space in the vectors to avoid mallocs
    outIndices.clear();
    outVertices.clear();
    outUvs.clear();
    outNormals.clear();

    outIndices.reserve(vertices.size());
    outVertices.reserve(vertices.size());
    outUvs.reserve(uvs.size());
    outNormals.reserve(vertices.size());

    std::map<glh::PackedVertex, unsigned int> vertexMap;

    // For each input vertex
    std::size_t size = vertices.size() / 3;

    for(std::size_t i = 0; i < size; ++i) {

        std::size_t idx = i * 3;
        std::size_t idx2 = i * 2;

        glh::PackedVertex packed(vertices[idx], vertices[idx + 1], vertices[idx + 2], uvs[idx2], uvs[idx2 + 1],
            normals[idx], normals[idx + 1], normals[idx + 2]);

        unsigned int index;
        bool found = getSimilarVertexIndex(packed, vertexMap, index);

        if(found) {
            outIndices.emplace_back(index);
            if(mRecomputeNormals) {
                for(std::size_t j = 0; j < 3; ++j)
                    outNormals[index + j] += normals[idx + j];
            }
        } else {
            for(std::size_t j = 0; j < 3; ++j) {
                outVertices.emplace_back(vertices[idx + j]);
                outNormals.emplace_back(normals[idx + j]);
                if(j < 2)
                    outUvs.emplace_back(uvs[idx2 + j]);
            }
            unsigned int newindex = (outVertices.size() / 3) - 1;
            outIndices.emplace_back(newindex);
            vertexMap[packed] = newindex;
        }
    }

    // Re-normalize the normals, tangents & bitangents
    if(mRecomputeNormals) {
        std::size_t nSize = outNormals.size() / 3;
        for(std::size_t n = 0; n < nSize; n++) {
            std::size_t idxN = n * 3;
            float x = outNormals[idxN];
            float y = outNormals[idxN + 1];
            float z = outNormals[idxN + 2];
            float l = std::sqrt(x * x + y * y + z * z);
            if(l != 0) {
                outNormals[idxN] = x / l;
                outNormals[idxN + 1] = y / l;
                outNormals[idxN + 2] = z / l;
            }
        }
    }

    std::vector<unsigned int>(outIndices).swap(outIndices);
    std::vector<float>(outVertices).swap(outVertices);
    std::vector<float>(outUvs).swap(outUvs);
    std::vector<float>(outNormals).swap(outNormals);
}

void glh::VboIndexer::process(const std::vector<float>& vertices,
    const std::vector<float>& uvs,
    const std::vector<float>& normals,
    std::vector<unsigned int>& outIndices,
    std::vector<float>& outVertices,
    std::vector<float>& outUvs,
    std::vector<float>& outNormals,
    std::vector<float>& outTangents,
    std::vector<float>& outBitangents)
{
    outIndices.clear();
    outVertices.clear();
    outUvs.clear();
    outNormals.clear();
    outTangents.clear();
    outBitangents.clear();

    computeTangent(vertices, normals, uvs);

    outIndices.reserve(vertices.size());
    outVertices.reserve(vertices.size());
    outUvs.reserve(uvs.size());
    outNormals.reserve(vertices.size());
    outTangents.reserve(vertices.size());
    outBitangents.reserve(vertices.size());

    // For each input vertex
    std::size_t size = vertices.size() / 3;

    for(std::size_t i = 0; i < size; ++i) {

        std::size_t idx = i * 3;
        std::size_t idx2 = i * 2;

        unsigned int index;
        glm::vec3 v = glm::vec3(vertices[idx], vertices[idx + 1], vertices[idx] + 2);
        glm::vec3 n = glm::vec3(normals[idx], normals[idx + 1], normals[idx] + 2);
        glm::vec2 u = glm::vec2(uvs[idx2], uvs[idx2 + 1]);
        bool found = getSimilarVertexIndex(v, u, n, outVertices, outUvs, outNormals, index);

        if(found) {
            outIndices.emplace_back(index);
            if(mRecomputeNormals) {
                for(std::size_t j = 0; j < 3; ++j)
                    outNormals[index + j] += normals[idx + j];
            }

            for(std::size_t j = 0; j < 3; ++j) {
                outTangents[index + j] += tangent[idx + j];
                outBitangents[index + j] += bitangent[idx + j];
            }

        } else {
            for(std::size_t j = 0; j < 3; ++j) {
                outVertices.emplace_back(vertices[idx + j]);
                outNormals.emplace_back(normals[idx + j]);
                outTangents.emplace_back(tangent[idx + j]);
                outBitangents.emplace_back(bitangent[idx + j]);
                if(j < 2)
                    outUvs.emplace_back(uvs[idx2 + j]);
            }
            unsigned int newindex = (outVertices.size() / 3) - 1;
            outIndices.emplace_back(newindex);
        }
    }

    // Re-normalize the normals, tangents & bitangents
    if(mRecomputeNormals) {
        std::size_t nSize = outNormals.size() / 3;
        for(std::size_t n = 0; n < nSize; n++) {
            std::size_t idxN = n * 3;
            float x = outNormals[idxN];
            float y = outNormals[idxN + 1];
            float z = outNormals[idxN + 2];
            float l = std::sqrt(x * x + y * y + z * z);
            if(l != 0) {
                outNormals[idxN] = x / l;
                outNormals[idxN + 1] = y / l;
                outNormals[idxN + 2] = z / l;
            }
        }
    }
}

bool glh::VboIndexer::getSimilarVertexIndex(glm::vec3& in_vertex,
    glm::vec2& in_uv,
    glm::vec3& in_normal,
    std::vector<float>& out_vertices,
    std::vector<float>& out_uvs,
    std::vector<float>& out_normals,
    unsigned int& result)
{
    // Lame linear search
    for(unsigned int i = 0; i < out_vertices.size() / 3; i++) {
        std::size_t idx = i * 3;
        std::size_t idx2 = i * 2;
        if(isNear(in_vertex.x, out_vertices[idx]) && isNear(in_vertex.y, out_vertices[idx + 1]) &&
            isNear(in_vertex.z, out_vertices[idx + 2]) && isNear(in_uv.x, out_uvs[idx2]) &&
            isNear(in_uv.y, out_uvs[idx2 + 1]) && isNear(in_normal.x, out_normals[idx]) &&
            isNear(in_normal.y, out_normals[idx + 1]) && isNear(in_normal.z, out_normals[idx + 2])) {
            result = i;
            return true;
        }
    }
    // No other vertex could be used instead.
    // Looks like we'll have to add it to the VBO.
    return false;
}

bool glh::VboIndexer::getSimilarVertexIndex(const PackedVertex& packed,
    std::map<PackedVertex, unsigned int>& vertexMap,
    unsigned int& result)
{
    std::map<PackedVertex, unsigned int>::iterator it = vertexMap.find(packed);
    if(it == vertexMap.end())
        return false;
    else {
        result = it->second;
        return true;
    }
}

void glh::VboIndexer::computeTangent(const std::vector<float>& positions,
    const std::vector<float>& normals,
    const std::vector<float>& uvs)
{
    if(positions.empty() && uvs.empty())
        return;

    bitangent.clear();
    tangent.clear();
    /*
        tangent.reserve(positions.size());
        bitangent.reserve(positions.size());
    */
    std::size_t posSize = positions.size() / 3;

    for(std::size_t j = 0; j < posSize; j += 3) {

        std::size_t i = 3 * j;
        std::size_t k = 2 * j;

        glm::vec3 v0(positions[i], positions[i + 1], positions[i + 2]);
        glm::vec3 v1(positions[i + 3], positions[i + 4], positions[i + 5]);
        glm::vec3 v2(positions[i + 6], positions[i + 7], positions[i + 8]);

        glm::vec2 uv0(uvs[k], uvs[k + 1]);
        glm::vec2 uv1(uvs[k + 2], uvs[k + 3]);
        glm::vec2 uv2(uvs[k + 4], uvs[k + 5]);

        // Edges of the triangle : postion delta
        glm::vec3 deltaPos1 = v1 - v0;
        glm::vec3 deltaPos2 = v2 - v0;

        // UV delta
        glm::vec2 deltaUV1 = uv1 - uv0;
        glm::vec2 deltaUV2 = uv2 - uv0;

        float f = 1.f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        glm::vec3 tan = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * f;
        tan = glm::normalize(tan);
        glm::vec3 bitan = (-deltaUV2.x * deltaPos1 + deltaUV1.x * deltaPos2) * f;
        bitan = glm::normalize(bitan);

        for(std::size_t a = 0; a < 3; ++a) {
            tangent.emplace_back(tan.x);
            tangent.emplace_back(tan.y);
            tangent.emplace_back(tan.z);

            bitangent.emplace_back(bitan.x);
            bitangent.emplace_back(bitan.y);
            bitangent.emplace_back(bitan.z);
        }
    }

    for(std::size_t i = 0; i < posSize; ++i) {
        std::size_t idx = i * 3;
        glm::vec3 n = glm::vec3(normals[idx], normals[idx + 1], normals[idx + 2]);
        glm::vec3 t = glm::vec3(tangent[idx], tangent[idx + 1], tangent[idx + 2]);
        glm::vec3 b = glm::vec3(bitangent[idx], bitangent[idx + 1], bitangent[idx + 2]);
        // Gram-Schmidt orthogonalize
        t = glm::normalize(t - n * glm::dot(n, t));
        // Calculate handedness
        if(glm::dot(glm::cross(n, t), b) < 0.0f) {
            t = t * -1.0f;
            tangent[idx] = t.x;
            tangent[idx + 1] = t.y;
            tangent[idx + 2] = t.z;
        }
    }
}

void glh::VboIndexer::recomputeNormals(const bool recompute)
{
    mRecomputeNormals = recompute;
}