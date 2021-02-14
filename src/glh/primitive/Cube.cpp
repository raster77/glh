#include "Cube.hpp"

glh::primitive::Cube::Cube()
    :   Primitive()
{
}

glh::primitive::Cube::~Cube()
{
}

void glh::primitive::Cube::create(const glm::vec3& size, const glm::ivec3& scale)
{
    mPositions.clear();
    mNormals.clear();
    mUvs.clear();
    mIndices.clear();

    vertexIndex = 0;

    // Front
    makePlane(0, 1, 2, size.x, size.y, scale.x, scale.y, size.z * 0.5f, 1, -1);
    // Back
    makePlane(0, 1, 2, size.x, size.y, scale.x, scale.y, -size.z * 0.5f, -1, -1);
    // Left
    makePlane(2, 1, 0, size.z, size.y, scale.z, scale.y, -size.x * 0.5f, 1, -1);
    // Right
    makePlane(2, 1, 0, size.z, size.y, scale.z, scale.y, size.x * 0.5f, -1, -1);
    // Top
    makePlane(0, 2, 1, size.x, size.z, scale.x, scale.z, size.y * 0.5f, 1, 1);
    // Bottom
    makePlane(0, 2, 1, size.x, size.z, scale.x, scale.z, -size.y * 0.5f, 1, -1);
    
    if(!mUseIndex)
        rebuild();
}

void glh::primitive::Cube::makePlane(const float u,
                                     const float v,
                                     const float w,
                                     const float su,
                                     const float sv,
                                     const float nu,
                                     const float nv,
                                     const float pw,
                                     const float flipu,
                                     const float flipv)
{
    std::size_t index = vertexIndex;
    for(std::size_t j = 0; j <= nv; j++) {
        for(std::size_t i = 0; i <= nu; i++) {

            std::vector<float> floats;
            floats.resize(3);

            floats[u] = (-su * 0.5f + i * su / nu) * flipu;
            floats[v] = (-sv * 0.5f + j * sv / nv) * flipv;
            floats[w] = pw;

            for(auto& f : floats)
                mPositions.emplace_back(f);

            floats[u] = 0.f;
            floats[v] = 0.f;
            floats[w] = pw / std::abs(pw);

            for(auto& f : floats)
                mNormals.emplace_back(f);

            mUvs.emplace_back(i / nu);
            mUvs.emplace_back(1.f - j / nv);
            vertexIndex++;
        }
    }

    for(std::size_t j = 0; j < nv; j++) {
        for(std::size_t i = 0; i < nu; i++) {
            std::size_t n = index + j * (nu + 1) + i;
            mIndices.emplace_back(n);
            mIndices.emplace_back(n + nu + 1);
            mIndices.emplace_back(n + nu + 2);
            mIndices.emplace_back(n);
            mIndices.emplace_back(n + nu + 2);
            mIndices.emplace_back(n + 1);
        }
    }
}
