#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include <vector>

namespace glh
{

namespace primitive
{

class Primitive
{
public:
    Primitive();
    virtual ~Primitive();

    const std::vector<float>& getPositions() const;
    const std::vector<float>& getNormals() const;
    const std::vector<float>& getUvs() const;
    const std::vector<unsigned int>& getIndices() const;
    const std::vector<float> getInterleavedBuffer() const;
    const bool isUsingIndex() const;
    void useIndex(const bool useIndex);

protected:
    const float PI = 3.14159265359f;
    const float TAU = 2.f * PI;
    std::vector<float> mPositions;
    std::vector<float> mNormals;
    std::vector<float> mUvs;
    std::vector<unsigned int> mIndices;
    bool mUseIndex;
    
    void rebuild();
};
}
}

#endif // PRIMITIVE_HPP
