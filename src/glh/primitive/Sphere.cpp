#include "Sphere.hpp"
#include <cmath>

glh::primitive::Sphere::Sphere()
    :   Primitive()
{
}

glh::primitive::Sphere::~Sphere()
{
}

void glh::primitive::Sphere::create(const float radius, const std::size_t xSegments, const std::size_t ySegments)
{

    for(std::size_t y = 0; y <= ySegments; ++y) {
        for(std::size_t x = 0; x <= xSegments; ++x) {
            float xSegment = static_cast<float>(x) / static_cast<float>(xSegments);
            float ySegment = static_cast<float>(y) / static_cast<float>(ySegments);
            float xPos = radius * std::cos(xSegment * TAU) * std::sin(ySegment * PI); // TAU is 2PI
            float yPos = radius * std::cos(ySegment * PI);
            float zPos = radius * std::sin(xSegment * TAU) * std::sin(ySegment * PI);

            mPositions.emplace_back(xPos);
            mPositions.emplace_back(yPos);
            mPositions.emplace_back(zPos);

            mNormals.emplace_back(xPos);
            mNormals.emplace_back(yPos);
            mNormals.emplace_back(zPos);

            mUvs.emplace_back(xSegment);
            mUvs.emplace_back(ySegment);
        }
    }

    for(std::size_t y = 0; y < ySegments; ++y) {
        for(std::size_t x = 0; x < xSegments; ++x) {
            mIndices.emplace_back((y + 1) * (xSegments + 1) + x);
            mIndices.emplace_back(y * (xSegments + 1) + x);
            mIndices.emplace_back(y * (xSegments + 1) + x + 1);

            mIndices.emplace_back((y + 1) * (xSegments + 1) + x);
            mIndices.emplace_back(y * (xSegments + 1) + x + 1);
            mIndices.emplace_back((y + 1) * (xSegments + 1) + x + 1);
        }
    }

    if(!mUseIndex) {
        rebuild();
    }

}
