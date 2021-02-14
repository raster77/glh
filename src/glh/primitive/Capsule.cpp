#include "Capsule.hpp"

glh::primitive::Capsule::Capsule()
    : Primitive()
{
}

glh::primitive::Capsule::~Capsule()
{
}

void glh::primitive::Capsule::create(const float radius,
    const float height,
    const std::size_t numSubdivisionsHeight,
    const std::size_t numSegments)
{
    mPositions.clear();
    mNormals.clear();
    mUvs.clear();
    mIndices.clear();

    float nsh = static_cast<float>(numSubdivisionsHeight);

    std::size_t ringsBody = numSubdivisionsHeight + 1;
    std::size_t ringsTotal = numSubdivisionsHeight + ringsBody;

    float bodyIncr = 1.f / (static_cast<float>(ringsBody) - 1.f);
    float ringIncr = 1.f / (nsh - 1);
    for(float r = 0.f; r < nsh * 0.5f; r++) {
        calculateRing(
            numSegments, radius, height, std::sin(PI * r * ringIncr), std::sin(PI * (r * ringIncr - 0.5f)), -0.5f);
    }

    for(std::size_t r = 0; r < ringsBody; r++) {
        calculateRing(numSegments, radius, height, 1.f, 0.f, static_cast<float>(r) * bodyIncr - 0.5f);
    }

    for(std::size_t r = numSubdivisionsHeight / 2; r < numSubdivisionsHeight; r++) {
        calculateRing(
            numSegments, radius, height, std::sin(PI * r * ringIncr), std::sin(PI * (r * ringIncr - 0.5f)), +0.5f);
    }

    for(std::size_t r = 0; r < ringsTotal - 1; r++) {
        for(std::size_t s = 0; s < numSegments - 1; s++) {
            mIndices.emplace_back((r * numSegments + (s + 1)));
            mIndices.emplace_back(r * numSegments + (s + 0));
            mIndices.emplace_back(((r + 1) * numSegments + (s + 1)));
            mIndices.emplace_back(((r + 1) * numSegments + (s + 0)));
            mIndices.emplace_back(((r + 1) * numSegments + (s + 1)));
            mIndices.emplace_back((r * numSegments + s));
        }
    }
}

void glh::primitive::Capsule::calculateRing(const std::size_t segments,
    const float radius,
    const float height,
    const float r,
    const float y,
    const float dy)
{
    float segIncr = 1.f / (static_cast<float>(segments) - 1.f);

    for(std::size_t s = 0; s < segments; s++) {
        float x = -std::cos((PI * 2) * s * segIncr) * r;
        float z = std::sin((PI * 2) * s * segIncr) * r;

        mPositions.emplace_back(radius * x);
        mPositions.emplace_back(radius * y + height * dy);
        mPositions.emplace_back(radius * z);

        mNormals.emplace_back(x);
        mNormals.emplace_back(y);
        mNormals.emplace_back(z);

        float u = (s * segIncr);
        float v = 0.5f - ((radius * y + height * dy) / (2.f * radius + height));
        mUvs.emplace_back(u);
        mUvs.emplace_back(1.f - v);
    }
}