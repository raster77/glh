#include "Torus.hpp"
#include <iostream>

glh::primitive::Torus::Torus()
    : Primitive()
{
}

glh::primitive::Torus::~Torus()
{
}

void glh::primitive::Torus::create(const float radius,
    const float tubularRadius,
    const std::size_t radialSegments,
    const std::size_t tubularSegments,
    const float arc)
{
    mPositions.clear();
    mNormals.clear();
    mUvs.clear();
    mIndices.clear();

    float rs = static_cast<float>(radialSegments);
    float ts = static_cast<float>(tubularSegments);

    for(std::size_t j = 0; j <= radialSegments; j++) {
        for(std::size_t i = 0; i <= tubularSegments; i++) {
            float u = static_cast<float>(i) / ts * arc;
            float v = static_cast<float>(j) / rs * PI * 2.f;

            glm::vec3 vertex((radius + tubularRadius * std::cos(v)) * std::cos(u),
                (radius + tubularRadius * std::cos(v)) * std::sin(u), tubularRadius * std::sin(v));
            mPositions.emplace_back(vertex.x);
            mPositions.emplace_back(vertex.y);
            mPositions.emplace_back(vertex.z);

            glm::vec3 center(radius * std::cos(u), radius * std::sin(u), 0.f);
            glm::vec3 normal = glm::normalize((vertex - center));
            mNormals.emplace_back(normal.x);
            mNormals.emplace_back(normal.y);
            mNormals.emplace_back(normal.z);
            
            mUvs.emplace_back(static_cast<float>(i) / ts);
            mUvs.emplace_back(static_cast<float>(j) / rs);
        }
    }
    
            for (std::size_t j = 1; j <= radialSegments; j++) {
            for (std::size_t i = 1; i <= tubularSegments; i++) {
                // indices
                unsigned int a = (tubularSegments + 1) * j + i - 1;
                unsigned int b = (tubularSegments + 1) * (j - 1) + i - 1;
                unsigned int c = (tubularSegments + 1) * (j - 1) + i;
                unsigned int d = (tubularSegments + 1) * j + i;
                // faces
                mIndices.emplace_back(a);
                mIndices.emplace_back(b);
                mIndices.emplace_back(d);
                mIndices.emplace_back(b);
                mIndices.emplace_back(c);
                mIndices.emplace_back(d);
            }
        }
}