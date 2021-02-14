#include "Primitive.hpp"

glh::primitive::Primitive::Primitive()
    : mUseIndex(true)
{
}

glh::primitive::Primitive::~Primitive()
{
}

const std::vector<float>& glh::primitive::Primitive::getPositions() const
{
    return mPositions;
}

const std::vector<float>& glh::primitive::Primitive::getNormals() const
{
    return mNormals;
}

const std::vector<float>& glh::primitive::Primitive::getUvs() const
{
    return mUvs;
}

const std::vector<unsigned int>& glh::primitive::Primitive::getIndices() const
{
    return mIndices;
}

const bool glh::primitive::Primitive::isUsingIndex() const
{
    return mUseIndex;
}

void glh::primitive::Primitive::useIndex(const bool useIndex)
{
    mUseIndex = useIndex;
}

const std::vector<float> glh::primitive::Primitive::getInterleavedBuffer() const
{
    std::vector<float> buffer;
    std::size_t totalSize = mPositions.size() + mUvs.size() + mNormals.size();
    buffer.reserve(totalSize);

    std::size_t size = mPositions.size() / 3;
    for(std::size_t i = 0; i < size; ++i) {
        std::size_t idx = i * 3;
        buffer.emplace_back(mPositions[idx]);
        buffer.emplace_back(mPositions[idx + 1]);
        buffer.emplace_back(mPositions[idx + 2]);

        buffer.emplace_back(mNormals[idx]);
        buffer.emplace_back(mNormals[idx + 1]);
        buffer.emplace_back(mNormals[idx + 2]);

        idx = i * 2;
        buffer.emplace_back(mUvs[idx]);
        buffer.emplace_back(mUvs[idx + 1]);
    }
    
    return buffer;
}

void glh::primitive::Primitive::rebuild()
{
    std::vector<float> tempPositions = mPositions;
    std::vector<float> tempNormals = mNormals;
    std::vector<float> tempUvs = mUvs;
    
    mPositions.clear();
    mNormals.clear();
    mUvs.clear();
    
    for(auto& i : mIndices) {
        std::size_t idx = i * 3;
        mPositions.emplace_back(tempPositions[idx]);
        mPositions.emplace_back(tempPositions[idx + 1]);
        mPositions.emplace_back(tempPositions[idx + 2]);
        
        mNormals.emplace_back(tempNormals[idx]);
        mNormals.emplace_back(tempNormals[idx + 1]);
        mNormals.emplace_back(tempNormals[idx + 2]);
        
        idx = i * 2;
        mUvs.emplace_back(tempUvs[idx]);
        mUvs.emplace_back(tempUvs[idx + 1]);
    }
}
