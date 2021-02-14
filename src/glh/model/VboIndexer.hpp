#ifndef VBOINDEXER_HPP
#define VBOINDEXER_HPP

#include <cmath>
#include <glm/detail/type_vec2.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/glm.hpp>
#include <map>
#include <vector>

namespace glh
{

struct PackedVertex {

    float vx;
    float vy;
    float vz;

    float uvx;
    float uvy;

    float nx;
    float ny;
    float nz;

    PackedVertex()
        : vx(0.f)
        , vy(0.f)
        , vz(0.f)
        , uvx(0.f)
        , uvy(0.f)
        , nx(0.f)
        , ny(0.f)
        , nz(0.f)
    {
    }

    PackedVertex(const float vx,
        const float vy,
        const float vz,
        const float uvx,
        const float uvy,
        const float nx,
        const float ny,
        const float nz)
        : vx(vx)
        , vy(vy)
        , vz(vz)
        , uvx(uvx)
        , uvy(uvy)
        , nx(nx)
        , ny(ny)
        , nz(nz)
    {
    }

    bool operator<(const PackedVertex& b) const
    {
        if(!isNear(vx, b.vx, 0.001f))
            return vx < b.vx;
        if(!isNear(vy, b.vy, 0.001f))
            return vy < b.vy;
        if(!isNear(vz, b.vz, 0.001f))
            return vz < b.vz;
        if(!isNear(uvx, b.uvx, 0.1f))
            return uvx < b.uvx;
        if(!isNear(uvy, b.uvy, 0.1f))
            return uvy < b.uvy;
        if(!isNear(nx, b.nx, 0.3f))
            return nx < b.nx;
        if(!isNear(ny, b.ny, 0.3f))
            return ny < b.ny;
        if(!isNear(nz, b.nz, 0.3f))
            return nz < b.nz;
        return false;
    };

private:
    bool isNear(const float v1, const float v2, const float margin = 0.01f) const
    {
        return std::abs(v1 - v2) < margin;
    }
};

template <class T> class PackedVertexHash;
template <> class PackedVertexHash<PackedVertex>
{
public:
    size_t operator()(const PackedVertex& v)
    {
        size_t vx = size_t(v.vx) * 100;
        size_t vy = size_t(v.vy) * 100;
        size_t vz = size_t(v.vz) * 100;

        size_t uvx = size_t(v.uvx) * 100;
        size_t uvy = size_t(v.uvy) * 100;

        size_t nx = size_t(v.nx) * 100;
        size_t ny = size_t(v.ny) * 100;
        size_t nz = size_t(v.nz) * 100;

        return (3 * vx + 5 * vy + 7 * vz + 9 * uvx + 11 * uvy + 13 * nx + 15 * ny + 17 * nz) % (1 << 16);
    }
};

class VboIndexer
{
public:
    VboIndexer();
    ~VboIndexer();

    void process(const std::vector<float>& vertices,
        const std::vector<float>& uvs,
        const std::vector<float>& normals,
        std::vector<unsigned int>& outIndices,
        std::vector<float>& outVertices,
        std::vector<float>& outUvs,
        std::vector<float>& outNormals);
    void process(const std::vector<float>& vertices,
        const std::vector<float>& uvs,
        const std::vector<float>& normals,
        std::vector<unsigned int>& outIndices,
        std::vector<float>& outVertices,
        std::vector<float>& outUvs,
        std::vector<float>& outNormals,
        std::vector<float>& outTangents,
        std::vector<float>& outBitangents);
    void recomputeNormals(const bool recompute);

private:
    bool getSimilarVertexIndex(glm::vec3& in_vertex,
        glm::vec2& in_uv,
        glm::vec3& in_normal,
        std::vector<float>& out_vertices,
        std::vector<float>& out_uvs,
        std::vector<float>& out_normals,
        unsigned int& result);
    bool getSimilarVertexIndex(const PackedVertex& packed,
        std::map<PackedVertex, unsigned int>& vertexMap,
        unsigned int& result);
    void computeTangent(const std::vector<float>& positions,
        const std::vector<float>& normals,
        const std::vector<float>& uvs);

    bool isNear(const float v1, const float v2, const float margin = 0.01f) const
    {
        return std::abs(v1 - v2) < margin;
    }

    bool mRecomputeNormals;
    std::vector<float> tangent;
    std::vector<float> bitangent;
};

#endif // VBOINDEXER_HPP
}