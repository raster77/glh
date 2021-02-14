#ifndef VERTEXATTRIBUTEPOINTER_HPP
#define VERTEXATTRIBUTEPOINTER_HPP

#include <glad/glad.h>
#include <vector>

namespace glh
{

class VertexAttributePointer
{
public:
    VertexAttributePointer();
    VertexAttributePointer(const unsigned int index, const unsigned int size, const unsigned int stride, const unsigned int offset);
    VertexAttributePointer(const unsigned int index,
        const unsigned int size,
        const GLenum glType,
        const bool normalized,
        const unsigned int stride,
        const unsigned int offset);
    ~VertexAttributePointer();

    void setIndex(const unsigned int index);
    void setSize(const unsigned int size);
    void setGlType(GLenum glType);
    void setNormalized(const bool normalized);
    void setStride(const unsigned int stride);
    void setOffset(const unsigned int offset);

    const GLenum getGlType() const;
    const unsigned int& getIndex() const;
    const bool& getNormalized() const;
    const unsigned int& getOffset() const;
    const unsigned int& getSize() const;
    const unsigned int& getStride() const;

    void enable();
    void disable();

private:
    unsigned int mIndex;
    unsigned int mSize;
    GLenum mGlType;
    bool mNormalized;
    unsigned int mStride;
    unsigned int mOffset;
    bool created;
    
    const static std::vector<GLenum> glTypes;
    
    bool isAllowed(const std::vector<GLenum>& values, const GLenum value);
};
}

#endif // VERTEXATTRIBUTEPOINTER_HPP
